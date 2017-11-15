gcc -g  rtpsend.c  -o  rtpsend  `pkg-config --cflags --libs  ortp`
gcc -g  rtprecv.c  -o  rtprecv  `pkg-config --cflags --libs  ortp`