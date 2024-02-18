## Raspberry Pi OS
<a href="https://www.raspberrypi.com/software/">ダウンロード</a><br>
<a href="https://www.raspberrypi.com/software/">![Imager](https://github.com/tmatsugaki/SocketClientServer/assets/922740/c70e6cca-fb1a-46ef-8cdc-b0fe612486c4)</a><br>
## Packages
sudo apt install -y build-essential<br>
sudo apt install -y cmake-dev<br>
sudo apt install -y libboost-all-dev<br>
sudo apt install -y libopencv-dev<br>
sudo apt install -y libcereal-dev<br>
sudo apt install -y libspdlog-dev<br>
## VNC Server
### 0.(macOSのみ) raspi-config の インターフェースオプションで RealVNC を macOS に適合させる
　<a href="https://daeudaeu.com/raspberry-pi-vnc-err/#confirm">ご参考</a>

RealVNC のオプション
<tt>Security
  Encription: Prefer off
  Authrntication: VNC Passwd</tt>

### 1.vncserver起動
pi@bullseye:~ $ vncserver<br>
See https://www.realvnc.com for information on VNC.

#### To start an instance of VNC Server in Virtual Mode, run the following command:<br>
  vncserver-virtual

#### To start the VNC Server in Virtual Mode daemon, run the following command as root:<br>
  /etc/vnc/vncservice start vncserver-virtuald

#### To start VNC Server in Service Mode, run the following command as root:<br>
  /etc/vnc/vncservice start vncserver-x11-serviced

#### To start VNC Server in User Mode, run the following command:<br>
  vncserver-x11

### 2.Listen ポート確認(TCP)
pi@bullseye:/etc $ netstat -ant | fgrep 59 -
tcp        0      0 0.0.0.0:5999            0.0.0.0:*               LISTEN     
tcp        0      0 0.0.0.0:5900            0.0.0.0:*               LISTEN     
tcp6       0      0 :::5999                 :::*                    LISTEN     
tcp6       0      0 :::5900                 :::*                    LISTEN     
pi@bullseye:/etc $ netstat -anu | fgrep 59 -
udp        0      0 0.0.0.0:5999            0.0.0.0:*                          
udp6       0      0 :::5999                 :::*         <br>

### 3.vncpasswd
pi@bullseye:~ $ vncpasswd<br>
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

pi@bullseye:~ $ sudo vncpasswd -service<br>
Setting "Password" VNC parameter for Service Mode server
Password:
Verify:
Successfully set "Password" VNC parameter in /root/.vnc/config.d/vncserver-x11
## VSCode for Windows
<a href="https://zenn.dev/boiledorange73/articles/0056-wsl-vsc-gcc">ご参考</a>
## VSCode機能拡張
WSL (Microsoft)<br>
C/C++v1.18.5 (Microsoft)<br>
C/C++ Extension Packv1.3.0 (Microsoft)<br>
C/C++ Themesv2.0.0 (Microsoft)<br>
CMake Toolsv1.17.15 (Microsoft)<br>
Japanese Language Pack for Visual Studio (Microsoft)<br>
Makefile Tools v0.8.22 プレビュー (Microsoft)<br>
Printv0.11.18 (Microsoft)<br>
Pylancev2024.2.2 (Microsoft)<br>
Pythonv2024.0.1 (Microsoft)<br>
Python Debuggerv2024.0.0 (Microsoft)<br>
## USB デバイスを接続する
<a href="https://learn.microsoft.com/ja-jp/windows/wsl/connect-usb#install-the-usbipd-win-project">ご参考</a>
※Windows11 にて試行中
