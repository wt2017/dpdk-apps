# dpdk-apps

# compile
gcc -o dpdk_reg_read main.c $(pkg-config --libs --cflags libdpdk)

# shared lib
export LD_LIBRARY_PATH=/usr/local/lib64:$LD_LIBRARY_PATH -> short solution

cat /etc/ld.so.conf.d/dpdk.conf -> long term solution
/usr/local/lib64
