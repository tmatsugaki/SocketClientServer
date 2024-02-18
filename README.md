###################################################################################<br>
【OS】<br>
![Imager](https://github.com/tmatsugaki/SocketClientServer/assets/922740/c70e6cca-fb1a-46ef-8cdc-b0fe612486c4)<br>
###################################################################################<br>
【Packages】
<code>
sudo apt install -y build-essential<br>
sudo apt install -y cmake-dev<br>
sudo apt install -y libboost-all-dev<br>
sudo apt install -y libopencv-dev<br>
sudo apt install -y libcereal-dev<br>
sudo apt install -y libspdlog-dev<br></code><br>
###################################################################################<br>
【VNC Server for Sonoma】<br>
0.raspi-config の インターフェースオプションで RealVNC をオンにし、下記で macOS(Sonoma)に適合させる<br>
<code><a href="https://daeudaeu.com/raspberry-pi-vnc-err/#confirm">https://daeudaeu.com/raspberry-pi-vnc-err/#confirm</a></code><br>
RealVNC のオプション<br>
<code>Security<br>
  Encription: Prefer off<br>
  Authrntication: VNC Passwd</code><br>
1.vncserver起動<br>
<code>pi@bullseye:~ $ vncserver
See https://www.realvnc.com for information on VNC.
To start an instance of VNC Server in Virtual Mode, run the following command:
  vncserver-virtual
To start the VNC Server in Virtual Mode daemon, run the following command as root:
  /etc/vnc/vncservice start vncserver-virtuald
To start VNC Server in Service Mode, run the following command as root:
  /etc/vnc/vncservice start vncserver-x11-serviced
To start VNC Server in User Mode, run the following command:
  vncserver-x11<br></code><br>
2.Listen ポート確認(TCP)<br>
<code>pi@bullseye:/etc $ netstat -ant | fgrep 59 -
tcp        0      0 0.0.0.0:5999            0.0.0.0:*               LISTEN     
tcp        0      0 0.0.0.0:5900            0.0.0.0:*               LISTEN     
tcp6       0      0 :::5999                 :::*                    LISTEN     
tcp6       0      0 :::5900                 :::*                    LISTEN     
pi@bullseye:/etc $ netstat -anu | fgrep 59 -
udp        0      0 0.0.0.0:5999            0.0.0.0:*                          
udp6       0      0 :::5999                 :::*         </code><br>
3.vncpasswd<br>
<code>
pi@bullseye:~ $ vncpasswd
VNC(R) Password Utility 7.5.1 (r50075) ARMv8-A (May 30 2023 13:19:26)
Copyright (C) RealVNC Ltd.
RealVNC and VNC are trademarks of RealVNC Ltd and are protected by trademark
registrations and/or pending trademark applications in the European Union,
United States of America and other jurisdictions.
Protected by UK patent 2481870; US patent 8760366; EU patent 2652951.
See https://www.realvnc.com for information on VNC.
For third party acknowledgements see:
https://www.realvnc.com/docs/7/foss.html
OS: Debian GNU/Linux 11, Linux 6.1.21, aarch64

Usage: vncpasswd [OPTION...] MODE

Mode:
  -user       Set the password for VNC Server in User Mode.
  -service    Set the password for VNC Server in Service Mode.
  -virtual    Set the password for VNC Server in Virtual Mode.
  -file FILE  Set the password in the file FILE.
  -print      Print the password to the console in a form suitable for
              configuration files and policy templates.
Options:
  -type TYPE  Set the password of type TYPE. VNC Server may support various
              types of password, including "ViewOnlyPassword",
              "AdminPassword", "GuestPassword", and
              "InputOnlyPassword". The default is "Password".
  -weakpwd    Permit the setting of a weak password (less than 6 characters).
              Not recommended.
  -legacy     Set the password using the legacy plaintext-equivalent
              (obfuscated) form, rather than as a salted hash.
              Not recommended.

pi@bullseye:~ $ sudo vncpasswd -service
Setting "Password" VNC parameter for Service Mode server
Password:
Verify:
Successfully set "Password" VNC parameter in /root/.vnc/config.d/vncserver-x11</code>
###################################################################################<br>
【VSCode for Windows】<br>
<code>https://zenn.dev/boiledorange73/articles/0056-wsl-vsc-gcc<br></code>
###################################################################################<br>
【VSCode　機能拡張】<br>
<ul>
<li>WSL (Microsoft)</li>
<li>C/C++v1.18.5 (Microsoft)</li>
<li>C/C++ Extension Packv1.3.0 (Microsoft)</li>
<li>C/C++ Themesv2.0.0 (Microsoft)</li>
<li>CMake Toolsv1.17.15 (Microsoft)</li>
<li>Japanese Language Pack for Visual Studio (Microsoft)</li>
<li>Makefile Tools v0.8.22 プレビュー (Microsoft)</li>
<li>Printv0.11.18 (Microsoft)</li>
<li>Pylancev2024.2.2 (Microsoft)</li>
<li>Pythonv2024.0.1 (Microsoft)</li>
<li>Python Debuggerv2024.0.0 (Microsoft)</li>
</ul>
###################################################################################<br>
