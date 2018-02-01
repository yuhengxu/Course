import requests
import json
import os
import time
from bs4 import BeautifulSoup
url="https://baike.baidu.com/item/"
m=input("请输入名字：")
s = requests.Session()
s.headers['User-Agent'] = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_2) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/34.0.1847.131 Safari/537.36'
r=s.get(url+m)
r.encoding=r.apparent_encoding
demo=r.text
soup=BeautifulSoup(demo,"html.parser")
p=soup.find_all("dt","basicInfo-item name")
t=soup.find_all("dd","basicInfo-item value")
data1=[]
for i in p:
    data1.append(i.text)
x=json.dumps(data1,ensure_ascii=False,indent=2)
data2=[]
for i in t:
    data2.append(i.text.strip())
y=json.dumps(data2,ensure_ascii=False,indent=2)
print(x)
print(y)
#爬取图片
items = soup.find_all('img')
folder_path = './photo/'  
if os.path.exists(folder_path) == False:  # 判断文件夹是否已经存在  
    os.makedirs(folder_path)  # 创建文件夹  
i=0 
for index,item in enumerate(items):  
    if i<5:         
        html = requests.get(item.get('src'))   # get函数获取图片链接地址，requests发送访问请求  
        img_name = folder_path + str(index + 1) +'.jpg'  
        with open(img_name, 'wb') as file:  # 以byte形式将图片数据写入  
            file.write(html.content)  
            file.flush()  
        file.close()  # 关闭文件  
        print('第%d张图片下载完成' %(index+1))  
        time.sleep(1)  # 自定义延时  
        i=i+1
