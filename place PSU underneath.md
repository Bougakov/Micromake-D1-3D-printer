# Placing PSU underneath Micromake D1 printer to save space

This tweak was initally described in this artcile on http://3dtoday.ru/blogs/sanja/hide-the-power-supply-delta-printer-under-body/; here is an extended version.

The purpose of this mod is to make Micromake D1 "monolitic" - so it could be carried in one piece easily. Another goal is to improve the safety of the PSU, because mains voltage is otherwise dangerously exposed.

![General view](https://pp.vk.me/c837423/v837423745/191ee/jvTvs92gLj0.jpg)

Here is the close-up. Pictured is the Orange PI PC computer that hosts Repetier Server and works as dedicated printer controller:

![Close-up](https://pp.vk.me/c837423/v837423745/191f8/CfGgooVEUl0.jpg)

I've started by cutting the triangle from OSB plate 2cm thick. It is easier to work with compared to wood and plywood, and it is heavier, which is good for a base plate. Use a sheet of A3 paper to make a template, glue it to the wood and cut with the oscillating saw. Use sandpaper attachment to polish the edges, then wipe it clean with cloth. Paint with the cheapest black aerosol paint in 2 layers, let it dry properly. Apply soft furniture pads on the bottom to protect your desk from scratches.

![Wooden plate](https://pp.vk.me/c837423/v837423745/1922a/pPJZcajPiyw.jpg)

Initially I used stock Micromake 16.5 amps PSU placed flat on the bottom, with the dedicated fan. But since the stock PSU turned to be garbage, I bought slightly larger 30A replacement PSU.

![Erdgeschoss](http://3dtoday.ru/upload/resize_cache/main/38a/940_1080_1/IMG_1205.JPG)

I have placed the new PSU on the left side, and used longer, 20cm M4 rods:

![With new PSU](https://pp.vk.me/c837423/v837423745/19216/J-xlr_UGyLE.jpg)

M4 rods are sold in 1m long pieces - you'd need two of these. Cut them to size with Dremel - and don't forget to wear eye protection in the process. I strongly suggest to use lockwashers to keep vertical rods in place:

![Lockwasher](http://xn--e1ahdoaefcbdgmy.xn--p1ai/wp-content/uploads/2013/10/shaiba-4.jpg)

Before tightening the nuts, place something flat, like a piece of glass, on top of all 6 rods. Make sure that the height of all of them is uniform, then tighten. You can optionally use a drop of the thread locking gel to ensure that the nuts stay in place despite all vibrations.

Next I've installed a power socket on the side. I bought it [from AliExpress for $1.2](https://alitems.com/g/1e8d1144949a590a4ec116525dc3e8/?ulp=https%3A%2F%2Fwww.aliexpress.com%2Fitem%2FNEW-10A-250V-Inlet-Module-Plug-Fuse-Switch-Male-Power-Socket-3-Pin-IEC320-C14%2F32505761611.html):

![Socket w/fuse](https://ae01.alicdn.com/kf/HTB1jyacKXXXXXckXFXXq6xXFXXXA/NEW-10A-250V-Inlet-Module-Plug-Fuse-Switch-Male-Power-Socket-3-Pin-IEC320-C14.jpg)

It comes without the fuse, so buy 20mm 2 amps one separately. Use copper wires to connect the PSU to the socket; ideally solder them and reliably insulate with heatshrink tubing. Either use crimp lugs or solder the ends of the wires that go into the terminal box of the PSU.

Use the M4 drill to clean six holes in the printer's corners from mold flash. Put a nut and the washer on each of the vertical rods at about 15cm height and put the printer on top. Then use 6 nuts to lock it in place.

---

This HOWTO was written for the [unofficial Facebook group of Micromake users](https://www.facebook.com/groups/173676226330714/) instead.

