 /*
rtpRecv.c
*/
#include <ortp/ortp.h>
#include <bctoolbox/vfs.h>
#include <signal.h>
#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#endif

int cond=1;

void stop_handler(int signum)
{
	cond=0;
}

void ssrc_cb(RtpSession *session)
{
	printf("hey, the ssrc has changed !\n");
}

static char *help="usage: rtprecv  filename loc_port [--format format] [--soundcard] [--noadapt] [--with-jitter <milliseconds>]\n";

#define MULAW 0
#define ALAW 1

#if defined(__hpux) && HAVE_SYS_AUDIO_H

#include <sys/audio.h>

int sound_init(int format)
{
	int fd;
	fd=open("/dev/audio",O_WRONLY);
	if (fd<0){
		perror("Can't open /dev/audio");
		return -1;
	}
	ioctl(fd,AUDIO_RESET,0);
	ioctl(fd,AUDIO_SET_SAMPLE_RATE,8000);
	ioctl(fd,AUDIO_SET_CHANNELS,1);
	if (format==MULAW)
		ioctl(fd,AUDIO_SET_DATA_FORMAT,AUDIO_FORMAT_ULAW);
	else ioctl(fd,AUDIO_SET_DATA_FORMAT,AUDIO_FORMAT_ALAW);
	return fd;	
}
#else
int sound_init(int format)
{
	return -1;
}
#endif

/*
================main==================================main==================================main==================
*/

int main(int argc, char*argv[])
{
	RtpSession *session;
	unsigned char buffer[160];
	int err;
	uint32_t ts=0;
	int stream_received=0;
	FILE *outfile;
	int local_port;
	int have_more;
	int i;
	int format=0;
	int soundcard=0;
	int sound_fd=0;
	int jittcomp=40;
	bool_t adapt=TRUE;
	
	/* init the lib */
	if (argc<3){
		printf("%s",help);
		return -1;
	}
	local_port=atoi(argv[2]);
	if (local_port<=0) {
		printf("%s",help);
		return -1;
	}

	outfile=fopen(argv[1],"wb");
	if (outfile==NULL) {
		perror("Cannot open file for writing");
		return -1;
	}
	
	
	if (soundcard){
		sound_fd=sound_init(format);
	}
	
	/*ortp init() 初始化*/
	ortp_init();
	ortp_scheduler_init();
	ortp_set_log_level_mask(NULL, ORTP_DEBUG|ORTP_MESSAGE|ORTP_WARNING|ORTP_ERROR);

	/* 设置信号处理函数 */
	signal(SIGINT,stop_handler);
	session=rtp_session_new(RTP_SESSION_RECVONLY);	
	rtp_session_set_scheduling_mode(session,1);
	rtp_session_set_blocking_mode(session,1);

	/*设置本地网络地址 端口号*/
	rtp_session_set_local_addr(session,"0.0.0.0",atoi(argv[2]),-1);
	rtp_session_set_connected_mode(session,TRUE);

	
	rtp_session_set_symmetric_rtp(session,TRUE);


	/*设置自适应补偿功能*/
	rtp_session_enable_adaptive_jitter_compensation(session,adapt);
	rtp_session_set_jitter_compensation(session,jittcomp);

	/*设置负载类型*/
	rtp_session_set_payload_type(session,0);

	/*设置信号回调函数*/
	rtp_session_signal_connect(session,"ssrc_changed",(RtpCallback)ssrc_cb,0);
	rtp_session_signal_connect(session,"ssrc_changed",(RtpCallback)rtp_session_reset,0);
	
	while(cond)
	{
		have_more=1;
		while (have_more){
			//Recv function
			err=rtp_session_recv_with_ts(session,buffer,160,ts,&have_more);

			if (err>0) stream_received=1;

			/* this is to avoid to write to disk some silence before the first RTP packet is returned*/	
			
			if ((stream_received) && (err>0)) 
			{
				//写缓冲到文件
				size_t ret = fwrite(buffer,1,err,outfile);

				if (sound_fd>0){

					ret = write(sound_fd,buffer,err);

					if (ret==-1)
					{
						fprintf(stderr,"write to sound card failed (%s)",strerror(errno));
					}

				}
			}
			
		}
		ts+=160;
		//ortp_message("Receiving packet.");
	}
	
	rtp_session_destroy(session);

	ortp_exit();
	
	ortp_global_stats_display();
	
	return 0;
}
