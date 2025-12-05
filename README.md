
# Yocto Project – Custom Image Build (qemux86-64)

This repository contains a Yocto Project setup along with a custom layer
(`meta-custom`) that is used to build user applications and integrate them into
a Yocto-based Linux image.  
The project is tested and successfully built for the **qemux86-64** machine.

---

##  Repository Structure

```

yocto/
│
├── poky/                 # Poky (Yocto reference distribution)
├── meta-openembedded/    # Community layers (if added)
├── meta-custom/          # Your custom layer containing recipes
│   ├── conf/
│   │   └── layer.conf
│   ├── recipes-apps/
│   ├── recipes-core/
│   ├── files/
│   └── ...
└── build/                # Build directory created after initialization

````

---

#  1. Setting Up the Yocto Build Environment

Clone this repository:

```bash
git clone https://github.com/SanthoshKappala/yocto.git
cd yocto
````

Initialize the build environment:

```bash
source poky/oe-init-build-env build
```

This creates:

```
build/conf/local.conf
build/conf/bblayers.conf
```

---

#  2. Add `meta-custom` to BBLAYERS

Edit:

```
build/conf/bblayers.conf
```

Add the custom layer:

```conf
BBLAYERS += "${TOPDIR}/../meta-custom"
```

Save and exit.

---

#  3. Configure local.conf

Open:

```
build/conf/local.conf
```

Set the machine:

```conf
MACHINE = "qemux86-64"
```

Optional (recommended):

```conf
EXTRA_IMAGE_FEATURES += "ssh-server-openssh package-management"
```

---

#  4. Building the Yocto Image

To build the default GUI image:

```bash
bitbake core-image-sato
```

To build a minimal base image:

```bash
bitbake core-image-minimal
```

If you have your own custom image in `meta-custom`:

```bash
bitbake custom-image
```

 Build time may take between 1–3 hours.

---

#  5. Running the Image in QEMU

Run the built image:

```bash
runqemu qemux86-64
```

CLI only:

```bash
runqemu qemux86-64 nographic
```

Your custom applications included in `meta-custom` will appear inside the
running QEMU virtual machine.

---

#  6. Adding Applications to `meta-custom`

Place your application files:

```
meta-custom/recipes-apps/myapp/files/main.c
```

Create a BitBake recipe:

```
meta-custom/recipes-apps/myapp/myapp_1.0.bb
```

Example recipe:

```bitbake
DESCRIPTION = "My Custom Application"
LICENSE = "MIT"

S = "${WORKDIR}"

SRC_URI = "file://main.c"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} main.c -o myapp
}

do_install() {
    install -d ${D}/usr/bin
    install -m 0755 myapp ${D}/usr/bin/
}
```

Add the app to your image:

Open:

```
build/conf/local.conf
```

Append:

```conf
IMAGE_INSTALL:append = " myapp"
```

---

#  7. Verifying the Layer

Run:

```bash
bitbake-layers show-layers
```

You should see:

```
meta-custom    <path>/meta-custom
```

If not, re-check your BBLAYERS path.

---

# ✔ Build Status

* ✅ Yocto environment setup complete
* ✅ meta-custom layer added
* ✅ Image successfully built for **qemux86-64**
* ✅ Custom applications compiled and installed into image
* ✅ QEMU boot verified

---

# 👤 Author

**Santhosh Kappala**
GitHub Repository:
[https://github.com/SanthoshKappala/yocto](https://github.com/SanthoshKappala/yocto)

