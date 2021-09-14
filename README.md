# openwrt-pkgs
my custom OpenWrt packages

Tested under OpenWrt 21.02 (Sep 14 2020)  
Linux kernel 5.4.143

* **call_qcsapi**: quantenna tools adapted for the Sercomm H500-s to make its wifi work.
* **luci-app-tn-vsftpd**: LuCI support for vsftpd. It requires vsftpd-uci package.
* **vsftpd-uci**: vsftpd mod with UCI support
* **phytool**: low level access to ethernet PHY like Marvell 88E1518
* **amule, libcryptopp, wxbase**: emule p2p client (ed2k downloads) and libraries required by amule
* **dump-cp15**: kernel module to dump the CP15 registers on ARM boards
* **dummy-irq**: kernel module to test external IRQs on GPIO lines
