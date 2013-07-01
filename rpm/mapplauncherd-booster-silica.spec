Name:       mapplauncherd-booster-silica
Summary:    Application launch booster for Silica
Version:    0.0.1
Release:    1
Group:      System/Applications
License:    TBD
URL:        https://bitbucket.org/jolla/ui-mapplauncherd-booster-silica
Source0:    %{name}-%{version}.tar.bz2
BuildRequires:  pkgconfig(QtCore) >= 4.8.0
BuildRequires:  pkgconfig(QtDeclarative)
BuildRequires:  pkgconfig(QtGui)
BuildRequires:  pkgconfig(x11)
BuildRequires:  mapplauncherd-devel >= 4.1.0
BuildRequires:  pkgconfig(qdeclarative-boostable)
Requires:  sailfishsilica
Requires:  mapplauncherd >= 4.1.0
Requires:  systemd-user-session-targets
Provides: mapplauncherd-booster-jolla > 0.0.6
Obsoletes: mapplauncherd-booster-jolla <= 0.0.6

%description
Application launch booster for Silica applications

%prep
%setup -q -n %{name}-%{version}

%build

%qmake 

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%qmake_install

mkdir -p %{buildroot}/usr/lib/systemd/user/user-session.target.wants || true
ln -s ../booster-silica.service %{buildroot}/usr/lib/systemd/user/user-session.target.wants/

%files
%defattr(-,root,root,-)
%{_libexecdir}/mapplauncherd/booster-silica
%{_datadir}/booster-silica/*
%{_libdir}/systemd/user/booster-silica.service
%{_libdir}/systemd/user/user-session.target.wants/booster-silica.service

