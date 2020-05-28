# OpenWorld2D
2D로 구현하는 오픈월드 프로젝트
<br>
자체 개발하는 isometric 기반인 2D 엔진을 기반으로 오픈월드를 만들어 가는 장기 프로젝트입니다.
<br>
제작 과정은 트위치( https://www.twitch.tv/codingstudio )에서 주로 낮에 생방송으로 진행하고 있습니다.
<br>
제작과정을 편집해 유튜브에도 올릴 예정에 있습니다.
<br>
<br>
[개발환경]<br>
OS : macOS Catalina<br>
언어 : C++<br>
개발툴 : QtCreator 4.12<br>
<br>
<br>
소스에 문의사항이 있으면 아래 이메일로 문의 주시기 바랍니다.<br>
<br>
email   : devlee.freebsd@gmail.com<br>
twitch  : https://www.twitch.tv/codingstudio<br>
youtube : https://www.youtube.com/channel/UCMj3LpAxKiBmPeScDkan0sg?view_as=subscriber<br>
<br>
<br>
Mac 에서 컴파일 오류 발생시<br>
     아래와 같은 오류가 발생한다면 qmake.conf에 문구를 추가한다.<br>
     "Undefined symbols for architecture x86_64"<br>
     QT설치디렉토리 : Qt/5.14.2/clang_64/mkspecs/macx-clang/qmake.conf<br>
     QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.9<br>
<br>
<br>
잉크스케이프 (Inkscape)<br>
<br>
프로그램에서 사용되는 isometric 다음과 같은 정보를 가진다.<br>
마름모 크기 : 40 x 20 pixel<br>
마름모 각도 : 26.565 도<br>
<br>
잉크스케이프 환경설정 방법<br>
파일 / 문서속성 / 격자<br>
생성 : 마름모 격자<br>
격자단위 : px<br>
기본 X : 0.0<br>
기본 Y : 0.0<br>
여백 Y : 20.0<br>
X 각도 : 26.57 (0.005도 차이가 있음)<br>
Y 각도 : 26.57 (0.005도 차이가 있음)<br>
<br>
