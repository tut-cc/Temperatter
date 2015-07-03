#!/usr/bin/ruby                                                                
#coding:utf-8                                                                  

require 'twitter'
require 'pp'
require 'date'

client = Twitter::REST::Client.new do |config|
  config.consumer_key =        "your consumer key"
  config.consumer_secret =     "your consumer secret"
  config.access_token =        "your access token"
  config.access_token_secret = "your access token secret"
end

def status1()
    res = `./ptemp2`
    return {"temp" => res.to_f}
end

def status2()
    filename = "/home/pi/tprt2_hi.dat"
    te = File.read(filename)
    return{"temp2" => te.to_f}
end
    
s1 = status1()
s2 = status2()
day = Time.now

#puts("#{s1['temp']}")
#puts("#{s2['temp2']}")

tn = s1['temp']
tp = s2['temp2']

if tn > tp
    client.update("#{day.hour}時#{day.min}分の気温は"+"#{sprintf("%.1f", tn)}度です。"+"先程より#{sprintf("%.1f", tn - tp)}℃上昇しました。 #Temperatter")
end

if tn < tp
    client.update("#{day.hour}時#{day.min}分の気温は"+"#{sprintf("%.1f", tn)}度です。"+"先程より#{sprintf("%.1f", tp - tn)}℃下降しました。 #Temperatter")
end

if tn == tp
    client.update("#{day.hour}時#{day.min}分の気温は"+"#{sprintf("%.1f", tn)}度です。"+"先程と変動ありません。 #Temperatter")
end

filename = "/home/pi/tprt2_hi.dat"
File.open(filename,'w') do |file|
  file.write("#{sprintf("%.1f", tn)}")
end
