# Metin2-InfluxDB

[![Tutorial - Metin2 Patcher Electron](https://img.youtube.com/vi/HTTu04XvWF4/0.jpg)](https://www.youtube.com/watch?v=HTTu04XvWF4 "Metin2 Grafana Statistics")

The purpose of this is to be able to create dashboards with the timeseries statistics, like the ones seen on the video made with Grafana.

Install InfluxDB: [https://docs.influxdata.com/influxdb/v2.1/install/](https://docs.influxdata.com/influxdb/v2.1/install/)

> ##### ℹ️ Information
>
> If you intend on using Cloudflare (and nginx as reverse proxy, since InfluxDB’s default port is 8086, which isn’t supported by Cloudflare, if you choose the docker installation, just map it to a port supported by Cloudflare, preferably HTTPS), you will need to create a firewall exception to bypass all rules that come from your metin2 game server so it doesn’t get blocked or challenged.
> 
> I recommend setting up nginx as reverse proxy, that way the port 443 can be used for all hosts configured on nginx.
> 
> On FreeBSD, only InfluxDB 1.8.* is available, not recommended, since the latest major stable version is 2.1. This tutorial was made for version 2.1, there may be differences on the requests.
>
> An IP address can be used, but a domain with SSL setup is preferable, for obvious reasons.

## InfluxDB Setup

### Create an organization
![Create an organization](https://i.imgur.com/v9RJzpK.png)

### Create a bucket
![Create a bucket](https://i.imgur.com/FP7jFbD.png)

## Lib cURL

### FreeBSD Setup
Install it:
```bash
pkg install curl
```

And link it on the Makefile:
```Makefile
-lcurl
```

### Windows Setup
For Windows it works with both vcpkg and compiling the lib manually.

Shared lib:
```bash
vcpkg install curl[openssl]:x86-windows
```

Static lib:
```bash
vcpkg install curl[openssl]:x86-windows-static
```

## Auto Event Manager

In case you already have this class/file, just compare and make the necessary changes. All the changes related to Influx are wrapped with the macro `INFLUX_STATS`.\
Don't forget to also make the necessary changes on `main.cpp`. If you are already using this you won't need to include the header and initialize the class.

## Edit Time

The default is send the data every 10 minutes.

On the file `InfluxData.cpp`, edit this code:
```c++
void CInfluxData::Check(int day, int hour, int minute, int second) {
    int lastNumber = minute % 10;

    if (isInfluxEnabled && lastNumber == 0 && second == 00)
```

If `lastNumber = 0`, then it means the number is divisible by, in this case, 10. Make sure when you edit the time to don't forget the seconds part, if you don't use it, it will run every second inside the minute you want to run it.

### Examples for other times

#### Every minute
```c++
    if (isInfluxEnabled && second == 00)
```

#### Every 5 minutes
```c++
    int lastNumber = minute % 5;
```

#### Every 30 seconds
```c++
    int lastNumber = seconds % 30;

    if (isInfluxEnabled && lastNumber == 0)
```

## Configuration

To use this make sure you have it only enabled on **ONE** core per channel, the online counter inside the channel is common between the cores, just add this on the CONFIG file to enable Influx on the core.
```
INFLUX_ENABLE: 1
```

The rest of the settings, can either be set on the source or by CONFIG options (this are the default values set on the source):
```
INFLUX_URL: http://127.0.0.1:8086
INFLUX_TOKEN: <token>
INFLUX_ORG: <organization>
INFLUX_BUCKET: <bucket>
```

## NodeJS Version

In case you don't to use the source, a NodeJS version is available where you can use the Metin2 API to get the user count and send it to Influx.

The source method is preferred.

## Acknowledgments:
[Gurgarath](https://metin2.dev/profile/17997-gurgarath/) for testing the tutorial on Windows.
[Deliris](https://metin2.dev/profile/11396-deliris/) for testing the tutorial on FreeBSD.