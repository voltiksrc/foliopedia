# Folio

Folio is a small terminal Wikipedia client written in C++.

You give it a search, it grabs the matching Wikipedia page, prints a short summary, and can show you the actual article URL if you want it.

## Usage

```bash
folio <search>
```

Examples:

```bash
folio Linux
```

```bash
folio Linus Torvalds
```

```bash
folio Arch Linux
```

Example output:

```text
Linux
-----
Linux is a family of free and open-source software Unix-like operating systems based on the Linux kernel, which was first released on 17 September 1991 by Linus Torvalds.

Do you want the URL? (y/n) y
Url: https://en.wikipedia.org/wiki/Linux
```

## Dependencies

Folio uses:

- C++
- libcurl
- nlohmann-json
- Meson
- Ninja

### Void Linux

Install the dependencies:

```bash
sudo xbps-install -S gcc meson ninja libcurl-devel nlohmann-json
```

## Clone

You can clone Folio from either GitHub or GitLab.

### GitHub

```bash
git clone https://github.com/voltiksrc/folio.git
cd folio
```

## Build

Set up the build directory:

```bash
meson setup build
```

Compile Folio:

```bash
meson compile -C build
```

Run it without installing:

```bash
./build/folio Linux
```

Example:

```bash
./build/folio Linus Torvalds
```

## Install

Install Folio system-wide:

```bash
sudo install -m 755 build/folio /usr/local/bin/folio
```

After that you can run it from anywhere:

```bash
folio Linux
```

```bash
folio Gentoo Linux
```

```bash
folio Linus Torvalds
```

```bash
folio C++
```

## Rebuilding

If you change the source code, rebuild it with:

```bash
meson compile -C build
```

Then reinstall the updated binary:

```bash
sudo install -m 755 build/folio /usr/local/bin/folio
```

## Uninstall

To remove Folio:

```bash
sudo rm /usr/local/bin/folio
```
