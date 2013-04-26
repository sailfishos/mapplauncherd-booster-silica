Name:       mapplauncherd-booster-jolla
Summary:    Application launch booster for Silica
Version:    0.0.1
Release:    1
Group:      System/Applications
License:    TBD
URL:        https://bitbucket.org/jolla/mapplauncherd-booster-jolla
Source0:    %{name}-%{version}.tar.bz2
BuildRequires:  pkgconfig(QtCore) >= 4.8.0
BuildRequires:  pkgconfig(QtDeclarative)
BuildRequires:  pkgconfig(QtGui)
BuildRequires:  pkgconfig(x11)
BuildRequires:  mapplauncherd-devel >= 4.1.0
BuildRequires:  pkgconfig(qdeclarative-boostable)
Requires:  sailfishsilica
Requires:  mapplauncherd >= 4.1.0

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

mkdir %{buildroot}/usr/lib/systemd/user/mapplauncherd.target.wants || true
ln -s ../booster-silica.service %{buildroot}/usr/lib/systemd/user/mapplauncherd.target.wants/

%files
%defattr(-,root,root,-)
%{_libexecdir}/mapplauncherd/booster-silica
%{_datadir}/booster-silica/*
%{_libdir}/systemd/user/booster-silica.service
%{_libdir}/systemd/user/mapplauncherd.target.wants/booster-silica.service

