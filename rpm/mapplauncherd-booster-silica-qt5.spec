Name:       mapplauncherd-booster-silica-qt5
Summary:    Application launch booster for Silica on QtQuick2
Version:    0.1.12
Release:    1
Group:      System/Applications
License:    Proprietary
URL:        https://bitbucket.org/jolla/ui-mapplauncherd-booster-silica
Source0:    %{name}-%{version}.tar.bz2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Gui)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(Qt5Concurrent)
BuildRequires:  mapplauncherd-devel >= 4.1.0
BuildRequires:  pkgconfig(qdeclarative5-boostable)
BuildRequires:  pkgconfig(Qt0Feedback)
BuildRequires:  pkgconfig(Qt5DBus)
BuildRequires:  pkgconfig(Qt5Sql)
BuildRequires:  pkgconfig(Qt5Svg)
BuildRequires:  pkgconfig(Qt5WaylandClient)
BuildRequires:  pkgconfig(Qt5Xml)
BuildRequires:  pkgconfig(Qt5XmlPatterns)
BuildRequires:  pkgconfig(libshadowutils)
BuildRequires:  pkgconfig(mlite5)
BuildRequires:  pkgconfig(ngf-qt5)
BuildRequires:  pkgconfig(gio-2.0)
BuildRequires:  pkgconfig(gmodule-2.0)
BuildRequires:  pkgconfig(gobject-2.0)
BuildRequires:  pkgconfig(timed-qt5)
Requires(pre):  shadow-utils
Requires:  sailfishsilica-qt5 >= 0.11.55
Requires:  mapplauncherd >= 4.1.0
Requires:  systemd-user-session-targets

%description
Application launch booster for Silica applications on QtQuick2

%package media
Summary:   Application launch booster for Silica/QtQuick2 with QtMultimedia
Group:     System/Application
BuildRequires:  pkgconfig(Qt5Multimedia)
Requires:  %{name} = %{version}-%{release}
Requires: qt5-qtdeclarative-import-multimedia
Requires: qt5-qtmultimedia-plugin-mediaservice-gstcamerabin >= 5.1.0+git25
Requires: qt5-qtmultimedia-plugin-mediaservice-gstmediaplayer
Requires:  nemo-qml-plugin-thumbnailer-qt5-video
Requires:  nemo-qml-plugin-thumbnailer-qt5
Requires:  nemo-qml-plugin-dbus-qt5
Requires:  nemo-qml-plugin-policy-qt5
Requires:  nemo-qml-plugin-time-qt5
Requires:  nemo-qml-plugin-configuration-qt5
Requires:  sailfish-components-gallery-qt5 >= 0.0.48

%description media
Application launch booster for Silica/QtQuick2 with QtMultimedia

%prep
%setup -q -n %{name}-%{version}

%build
# We intentionally disable LD_AS_NEEDED in order to be able to link to libraries that we do not use symbols from.
unset LD_AS_NEEDED
%qmake5 

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%qmake_install

mkdir -p %{buildroot}/usr/lib/systemd/user/user-session.target.wants || true
ln -s ../booster-silica-qt5.service %{buildroot}/usr/lib/systemd/user/user-session.target.wants/
ln -s ../booster-silica-media.service %{buildroot}/usr/lib/systemd/user/user-session.target.wants/

%pre
groupadd -rf privileged

%files media
%defattr(-,root,root,-)
%attr(2755, root, privileged) %{_libexecdir}/mapplauncherd/booster-silica-media
%{_datadir}/booster-silica-media/preload.qml
%{_libdir}/systemd/user/booster-silica-media.service
%{_libdir}/systemd/user/user-session.target.wants/booster-silica-media.service

%files
%defattr(-,root,root,-)
%attr(2755, root, privileged) %{_libexecdir}/mapplauncherd/booster-silica-qt5
%{_datadir}/booster-silica-qt5/preload.qml
%{_libdir}/systemd/user/booster-silica-qt5.service
%{_libdir}/systemd/user/user-session.target.wants/booster-silica-qt5.service

