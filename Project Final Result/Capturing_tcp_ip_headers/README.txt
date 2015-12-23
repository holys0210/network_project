How to run

Compile
# gcc -Wall -o test nfqnl_test.c -lnfnetlink -lnetfilter_queue

1st console
# sudo ./test

2nd console
# sudo iptables -A OUTPUT -p tcp -j NFQUEUE
