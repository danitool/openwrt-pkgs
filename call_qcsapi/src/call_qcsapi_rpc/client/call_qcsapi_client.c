/*SH0
*******************************************************************************
**                                                                           **
**         Copyright (c) 2011 Quantenna Communications Inc                   **
**                                                                           **
**  File        : call_qcsapi_sockrpcd.c                                     **
**  Description : Wrapper from rpc server daemon to call_qcsapi,             **
**                starting from an rpcgen generated server stub.             **
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

#include <stdio.h>
#include <errno.h>
#include <rpc/rpc.h>
#include <call_qcsapi_rpc/generated/call_qcsapi_rpc.h>

int call_qcsapi_rpc_client(CLIENT *clnt, int argc, char **argv)
{
	enum clnt_stat retval;
	struct call_qcsapi_rpc_result result;
	struct call_qcsapi_rpc_request request;
	int ret;

	memset(&request, 0, sizeof(request));
	memset(&result, 0, sizeof(result));
	request.argv.argv_len = argc;
	request.argv.argv_val = argv;

	if (argc > 1 && !strcmp(argv[1], "flash_image_update")) {
		struct timeval tv = {.tv_sec = 60, .tv_usec = 0};
		/* After sending a request to the server, a client program waits for a
		 * default period (25 seconds) to receive a reply, but 25 seconds is not
		 * enough for flash_image_update to complete. Setting timeout to 60 seconds
		 * for this commands.
		 */
		clnt_control(clnt, CLSET_TIMEOUT, (char *)&tv);
	}

	retval = call_qcsapi_remote_1(&request, &result, clnt);
	if (retval != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
		clnt_perrno (retval);
		ret = -ENOLINK;
	} else {
		ret = result.return_code;
		if (result.stdout_produced)
			fputs(result.stdout_produced, stdout);
		if (result.stderr_produced)
			fputs(result.stderr_produced, stderr);
	}

	return ret;
}

