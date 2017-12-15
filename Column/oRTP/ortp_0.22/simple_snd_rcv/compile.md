gcc -g rtpsend.c -o rtpsend -I/home/wgwei/0.22/ortp-0.22.0/include  -L/home/wgwei/0.22/ortp-0.22.0/src/.libs/ -lortp
gcc -g rtprecv.c -o rtprecv -I/home/wgwei/0.22/ortp-0.22.0/include  -L/home/wgwei/0.22/ortp-0.22.0/src/.libs/ -lortp
export LD_LIBRARY_PATH=/home/wgwei/0.22/ortp-0.22.0/src/.libs:$LD_LIBRARY_PATH
