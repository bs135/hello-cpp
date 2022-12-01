DESCRIPTION = "Simple hello-cpp application"
SECTION = "examples"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRCREV = "${AUTOREV}"
SRCBRANCH ?= "master"
SRVNAME = "hello-cpp.service"
SRC_URI = "git://github.com/bs135/hello-cpp.git;protocol=https;branch=${SRCBRANCH}"

S = "${WORKDIR}/git"

DEPENDS += " nlohmann-json hiredis redis-plus-plus"
# RDEPENDS_${PN} += "hiredis redis-plus-plus"

TARGET_CC_ARCH += "${LDFLAGS}"
# INSANE_SKIP_${PN} = "ldflags"
# INSANE_SKIP_${PN}-dev = "ldflags"

# RDEPENDS_${PN} += " libdotenv.so()(64bit)"
# PROVIDES = " libdotenv"
# RPROVIDES_${PN} += " libdotenv.so()(64bit)"
# FILES_${PN} += " ${libdir}/libabc.so"

#Pack the path
FILES_${PN} += "/home/root"
FILES_${PN} += "/lib/systemd/system"

REQUIRED_DISTRO_FEATURES= "systemd"

SYSTEMD_SERVICE_${PN} = "${SRVNAME}"

inherit cmake systemd features_check

# do_compile() {
# 	LDFLAGS += -lpthread
# 	oe_runmake
# }

do_install() {
	install -d ${D}${bindir}
	install -m 0755 hello-cpp ${D}${bindir}

	# install -d ${D}${libdir}
	# install -m 0644 extlib/dotenv/libdotenv.so ${D}${libdir}

	install -d ${D}/etc/hello-cpp
	install -m 0644 ${S}/.env.example ${D}/etc/hello-cpp/.env

	install -d ${D}${systemd_unitdir}/system
	install -m 0644 ${S}/service/${SRVNAME} ${D}${systemd_unitdir}/system
}

# do_configure_prepend() {
# 	cd ${S}
# 	git submodule update --init --recursive
# }

# do_configure {
# }