/*SH0
*******************************************************************************
**                                                                           **
**         Copyright (c) 2014 Quantenna Communications Inc                   **
**                                                                           **
*******************************************************************************
**                                                                           **
**  Redistribution and use in source and binary forms, with or without       **
**  modification, are permitted provided that the following conditions       **
**  are met:                                                                 **
**  1. Redistributions of source code must retain the above copyright        **
**     notice, this list of conditions and the following disclaimer.         **
**  2. Redistributions in binary form must reproduce the above copyright     **
**     notice, this list of conditions and the following disclaimer in the   **
**     documentation and/or other materials provided with the distribution.  **
**  3. The name of the author may not be used to endorse or promote products **
**     derived from this software without specific prior written permission. **
**                                                                           **
**  Alternatively, this software may be distributed under the terms of the   **
**  GNU General Public License ("GPL") version 2, or (at your option) any    **
**  later version as published by the Free Software Foundation.              **
**                                                                           **
**  In the case this software is distributed under the GPL license,          **
**  you should have received a copy of the GNU General Public License        **
**  along with this software; if not, write to the Free Software             **
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA  **
**                                                                           **
**  THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR       **
**  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES**
**  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  **
**  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,         **
**  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT **
**  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,**
**  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    **
**  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT      **
**  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF **
**  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.        **
**                                                                           **
*******************************************************************************
EH0*/

#include <rpc/rpc.h>
#include <qcsapi_rpc_common/common/rpc_raw.h>
#include <call_qcsapi_rpc/client/call_qcsapi_client.h>
#include <call_qcsapi_rpc/generated/call_qcsapi_rpc.h>
#include <qcsapi_rpc_common/client/qftc.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int ret;
	CLIENT *clnt;
	uint8_t dst_mac[ETH_HLEN];

	if (geteuid()) {
		printf("QRPC: only root can do that\n");
		exit(1);
	}

	if (argc < 4) {
		printf("Usage: %s <source ifname> <dest mac addr> <QCSAPI command> [<arg> ...]\n",
			argv[0]);
		exit(1);
	}

	if (str_to_mac(argv[2], dst_mac) < 0) {
		printf("QRPC: Wrong destination MAC address format. "
			"Use the following format: XX:XX:XX:XX:XX:XX\n");
		exit(1);
	}

	clnt = qrpc_clnt_raw_create(CALL_QCSAPI_PROG, CALL_QCSAPI_VERS, argv[1],
		dst_mac, QRPC_CALL_QCSAPI_RPCD_SID);
	if (clnt == NULL) {
		clnt_pcreateerror("QRPC: ");
		exit(2);
	}

	argv[2] = argv[0];
	ret = call_qcsapi_rpc_client(clnt, argc - 2, &argv[2]);

	clnt_destroy(clnt);

	if (!ret && !strcmp(argv[3], "send_file")) {
		if (qftc_start(argv[4], argv[1], dst_mac) < 0) {
			printf("send_file command failed\n");
		} else {
			printf("complete\n");
		}
	}

	return ret;
}
