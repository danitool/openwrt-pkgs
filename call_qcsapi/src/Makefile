
CC = gcc
CFLAGS = -I/usr/include/tirpc -I. -O -g -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -fstrict-aliasing
LDFLAGS = -ltirpc

COMMON_OBJS = \
	call_qcsapi_rpc/generated/call_qcsapi_rpc_clnt.o	\
	call_qcsapi_rpc/generated/call_qcsapi_rpc_xdr.o		\
	call_qcsapi_rpc/client/call_qcsapi_client.o		\

OBJS_SOCKET_RAW = $(COMMON_OBJS)	\
	call_qcsapi_rpc/client/socket_raw/call_qcsapi_sockraw.o \
	qcsapi_rpc_common/client/rpc_raw_clnt.o			\
	qcsapi_rpc_common/common/rpc_raw.o			\
	qcsapi_rpc_common/client/qftc.o				\

OBJS_SOCKET = $(COMMON_OBJS)	\
	call_qcsapi_rpc/client/socket/call_qcsapi_sockrpc.o	\
	qcsapi_rpc_common/client/find_host_addr.o		\
	qcsapi_rpc_common/common/rpc_raw.o			\
	qcsapi_rpc_common/client/qftc.o				\

TARGETS = call_qcsapi_sockrpc call_qcsapi_raw

all: $(TARGETS)

-include $(shell find . -name \*.d)

call_qcsapi_sockrpc: $(OBJS_SOCKET:%=build/%)
	${CC} ${LDFLAGS} $^ -o $@

call_qcsapi_raw: $(OBJS_SOCKET_RAW:%=build/%)
	${CC} ${LDFLAGS} $^ -o $@

build/%.o: %.c
	@mkdir -p ${@D}
	${CC} ${LDFLAGS} ${CFLAGS} $< -c -o $@ -MD -MF $@.d

clean:
	rm -rf build $(TARGETS)

