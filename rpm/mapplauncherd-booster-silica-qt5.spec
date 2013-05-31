Name:       mapplauncherd-booster-silica-qt5
Summary:    Application launch booster for Silica on QtQuick2
Version:    0.0.1
Release:    1
Group:      System/Applications
License:    TBD
URL:        https://bitbucket.org/jolla/ui-mapplauncherd-booster-silica
Source0:    %{name}-%{version}.tar.bz2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Gui)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(Qt5Concurrent)
BuildRequires:  mapplauncherd-devel >= 4.1.0
BuildRequires:  pkgconfig(qdeclarative5-boostable)
Requires:  sailfishsilica-qt5
Requires:  mapplauncherd >= 4.1.0

%description
Application launch booster for Silica applications on QtQuick2

%prep
%setup -q -n %{name}-%{version}

%build

%qmake5 

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%qmake_install

mkdir %{buildroot}/usr/lib/systemd/user/mapplauncherd.target.wants || true
ln -s ../booster-silica-qt5.service %{buildroot}/usr/lib/systemd/user/mapplauncherd.target.wants/

%files
%defattr(-,root,root,-)
%{_libexecdir}/mapplauncherd/booster-silica-qt5
%{_datadir}/booster-silica-qt5/*
%{_libdir}/systemd/user/booster-silica-qt5.service
%{_libdir}/systemd/user/mapplauncherd.target.wants/booster-silica-qt5.service
