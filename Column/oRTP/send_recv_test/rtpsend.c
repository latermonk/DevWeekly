/*
rtpsend.c 
send rtp package program
*/

#include <ortp/ortp.h>
#include <signal.h>
#include <stdlib.h>

#ifndef _WIN32 
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#endif

int runcond=1;

void stophandler(int signum)
{
	runcond=0;
}

static const char *help="usage: rtpsend	filename dest_ip4addr dest_port [ --with-clockslide <value> ] [ --with-jitter <milliseconds>]\n";

int main(int argc, char *argv[])
{
    /*
     变量初始化
     */
	RtpSession *session;
	unsigned char buffer[160];
	int i;
	FILE *infile;
	char *ssrc;
	uint32_t user_ts=0;
	int clockslide=0;
	int jitter=0;
	
    /*
     系统初始化
     */
    //初始化oRTP库
	ortp_init();  //初始化oRTP库
    
    //调度器初始化  scheduler可以管理多个session 接收端可以通过select接受多个session
	ortp_scheduler_init();
    
    //设置日志级别
	ortp_set_log_level_mask(NULL, ORTP_MESSAGE|ORTP_WARNING|ORTP_ERROR);
    
    //新建RTP会话  sendonly recvonly sendrecv 此会话如果能够发送数据的话  输出流会被赋予一个随机的SSRC数
	session=rtp_session_new(RTP_SESSION_SENDONLY);
	
	//设置RTP会话的调度模式 第二个参数为真时 表示可以使用调度模式 如阻塞模式
	rtp_session_set_scheduling_mode(session,1);//

	//第二个参数为真时 使能调度模式 会直接影响 rtp_session_send_with_ts() & rtp_session_recv_with_ts()的行为
	rtp_session_set_blocking_mode(session,1);

	//一个connect（）在第一个数据包接收后将对源地址进行使用
	//连接一个socket会造成拒绝说有不是connect()里边指定的地址发来的数据
	rtp_session_set_connected_mode(session,TRUE);

	//设置IP与端口
	rtp_session_set_remote_addr(session,argv[2],atoi(argv[3]));

	//设置负载类型
	//默认值为0
	//根据 https://www.iana.org/assignments/rtp-parameters/rtp-parameters.xhtml 描述
	// 0为PCMU编码  18为G729编码  34为H263编码
	rtp_session_set_payload_type(session,0);
	
	//从环境变量中获取SSRC并设置到rtpSession中
	ssrc=getenv("SSRC");
	if (ssrc!=NULL) {
		printf("using SSRC=%i.\n",atoi(ssrc));

		//设置到rtpSession中
		rtp_session_set_ssrc(session,atoi(ssrc));
	}
		
	#ifndef _WIN32
	infile=fopen(argv[1],"r");
	#else
	infile=fopen(argv[1],"rb");
	#endif

	if (infile==NULL) {
		perror("Cannot open file");
		return -1;
	}

	signal(SIGINT,stophandler);
	while( ((i=fread(buffer,1,160,infile))>0) && (runcond) )
	{
		//发送RTP包
		rtp_session_send_with_ts(session,buffer,i,user_ts);
		user_ts+=160;

		/*
		if (clockslide!=0 && user_ts%(160*50)==0){
			ortp_message("Clock sliding of %i miliseconds now",clockslide);
			rtp_session_make_time_distorsion(session,clockslide);
		}
		*/
		/*this will simulate a burst of late packets */
		/*
		if (jitter && (user_ts%(8000)==0)) {
			ortp_message("Simulating late packets now (%i milliseconds)",jitter);
			ortp_sleep_ms(jitter);
		}
		*/
	}

	fclose(infile);
	rtp_session_destroy(session);
	ortp_exit();
	ortp_global_stats_display();

	return 0;
}
