Name:       mapplauncherd-booster-jolla
Summary:    Applauncherd booster plugin for Jolla Components
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
BuildRequires:  mapplauncherd-devel >= 4.0.0
Requires:  sailfishsilica
Requires:  mapplauncherd >= 4.0.0

%description
Applauncherd booster plugin for Jolla Components applications

%prep
%setup -q -n %{name}-%{version}

%build

%qmake 

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%qmake_install

%files
%defattr(-,root,root,-)
%{_libdir}/applauncherd/libjollabooster.so
%{_datadir}/jollabooster/*

