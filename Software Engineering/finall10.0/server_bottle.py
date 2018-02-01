#/usr/bin/env python
#coding=utf-8

import pymysql
import json
import string
import random
import urllib
import urllib.request
import sys
import os,re
import time
import requests
from bottle import *
from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.common.desired_capabilities import DesiredCapabilities




pro_path = os.path.split(os.path.realpath(__file__))[0]
sys.path.append(pro_path)



# 
#查询登录信息
def check_login(username, password):  
    a_list = []
    if username is not None or password is not None:
            #连接数据库
            conn = pymysql.connect(user='root', passwd='8520', db='user')   
            cursor = conn.cursor() # 创建数据游标
            # 执行查询
            # query = ("SELECT username, password FROM  userinfo WHERE username=%s and password=%s")
            # print("*************************2***********************")
            # cursor.execute(query, (username, password))
            # print("*************************3***********************")
            # a_list = cursor.fetchall() # fetchone获取一个元组
            # count = int(cursor.rowcount)  # 获取元组个数 
            # if count:
            #     return 1
            # else:
            #     return 0
            query = ("SELECT username FROM  userinfo WHERE username=%s")
            cursor.execute(query, (username))
            count = int(cursor.rowcount)  # 获取元组个数 
            if count:
                #该用户已注册过
                query = ("SELECT username, password FROM  userinfo WHERE username=%s and password=%s")
                cursor.execute(query, (username, password))
                count = int(cursor.rowcount)  # 获取元组个数 
                if count:
                    #密码正确允许登录返回1
                    return 1
                else: 
                    return 2   #密码不正确返回0
            else:
                return 0    #该用户未注册

        
         #finally:
            conn.commit()  # 提交修改
            cursor.close() # 关闭数据库
            conn.close()



# 定义assets路径，即静态资源路径，如css,js,及样式中用到的图片等
assets_path = '/'.join((pro_path,'assets'))
@route('/assets/<filename:re:.*\.css|.*\.js|.*\.png|.*\.jpg|.*\.gif>')
def server_static(filename):
    """定义/assets/下的静态(css,js,图片)资源路径"""
    return static_file(filename, root=assets_path)


@route('/home')
def index():
    return template('home')

@route('/index')
def index():
    return template('index')

@route('/search')
def home():
    return template('search')

@route('/signup')
def signup():
    return template('signup')

#登录端口
@route('/index',method="post")
def sign_in():
    username=request.forms.get('username')
    password=request.forms.get('password')
    print (username) 
    print (password)
    key = check_login(username, password)
    if key == 1:
        return '1'
    elif key == 2:
        return '2'
    else:
        return '0'


#注册端口
@route('/signup',method="post")
def sign_up():
    username=request.forms.get('username')
    password=request.forms.get('password')
    print (username) 
    print (password)
    conn = pymysql.connect(user='root', passwd='8520', db='user')   
    cursor = conn.cursor() # 创建数据游标
    query = ("SELECT username FROM  userinfo WHERE username=%s")
    cursor.execute(query, (username))
    count = int(cursor.rowcount)  # 获取元组个数 
    if count:
        #该用户已被注册，返回
        return '0'
    else:
        #没有被注册过，插入数据库
        query = ("INSERT INTO userinfo(username,password)VALUES (%s, %s)")
        cursor.execute(query, (username, password))
        #finally:
        conn.commit()  # 提交修改
        cursor.close() # 关闭数据库
        conn.close()
        return '1'







#查询端口
@route('/home',method="post")
def pachong():
    response.set_header('Access-Control-Allow-Origin','*')
    url="https://baike.baidu.com/item/"
    print("***************************************")
    m = request.body.readlines()[0].decode('utf8')[7:]
    #m = request.query.msearch
    #m = "杨幂"
    print(m)
    print("***************************************")
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
    
    data2=[]
    for i in t:
        data2.append(i.text.strip())

    x=json.dumps(data1,ensure_ascii=False,indent=2)
    y=json.dumps(data2,ensure_ascii=False,indent=2)
    # print(x)
    # print(y)

    #对返回的json字符串进行处理，每个数组用 $ 隔开
    data1.append('$')
    data2.append('$')
    data1=data1+data2
    z=json.dumps(data1,ensure_ascii=False,indent=2)
    # print(z)
    q=len(data1)
    # print(q)
    # print(data1)


    ################超哥###################
    dcap = dict(DesiredCapabilities.PHANTOMJS)
    dcap['phantomjs.page.settings.userAgent'] = ('Mozilla/5.0 (Macintosh; Intel Mac OS X 10.9; rv:25.0) Gecko/20100101 Firefox/25.0 ')

    driver = webdriver.PhantomJS(desired_capabilities=dcap)

    #此处为网址。。。text=‘演员名’,可以为接口！！！！！
    s = m
    th = urllib.parse.quote(s)
    url='https://movie.douban.com/subject_search?search_text='+th+'&cat=1002'
    driver.set_page_load_timeout(30)
    driver.get(url)
    time.sleep(2)


    movies=driver.find_elements_by_class_name('title-text')
    #电影名movies

    datas=driver.find_elements_by_class_name('rating_nums')
    #评分datas

    time.sleep(1)

    #types=driver.find_elements_by_class_name('metaabstract')


    #performers=driver.find_elements_by_class_name('metaabstract_2')


    content=driver.page_source

    reg=u'<.*?img.*?src="(.*?)".*?class="cover">'

    reg1=u'<div.*?class="meta.*?abstract">(.*?)</div>'

    reg2=u'<div.*?class="meta.*?abstract_2">(.*?)</div>'

    imglist=re.findall(reg,content)
    #表示图片

    types=re.findall(reg1,content)
    #类型types

    performers=re.findall(reg2,content)
    #主演performers

    xx=[]
    yy=[]
    zz=[]
    hh=[]
    pp=[]

    #driver.close()
    i=6

    for img in imglist:
        if(i<12):
            pp.append(img)
            print(img)
            str1=str(i)
            urllib.request.urlretrieve(img, "./assets"+os.sep+str1+".jpg")
            i=i+1
    #此处将图片保存在文件里

    picture=json.dumps(pp)


    for movie in movies:
        if(movie!=movies[0]):
            xx.append(movie.text)

    name=json.dumps(xx)


    for data in datas:
        yy.append(data.text)

    grade=json.dumps(yy)

    for type in types:
        zz.append(type)

    style= json.dumps(zz)

    for performer in performers:
        hh.append(performer)

    actor = json.dumps(hh)

    xx.append('$') #电影名
    yy.append('$') #分数
    zz.append('$') #类型
    hh.append('$') #主演
    pp.append('$') #图片网站
    data1=data1+xx 
    data1=data1+yy
    data1=data1+zz
    data1=data1+hh
    data1=data1+pp
    # print(data1)
    #picture为json的图片网址
    #name为json的电影名
    #grade为json的评分
    #style为json的类型介绍
    #actor为json的演员介绍

    driver.quit()

    #爬取图片
    # items = soup.find_all('img')
    # folder_path = './assets/'  
    # if os.path.exists(folder_path) == False:  # 判断文件夹是否已经存在  
    #     os.makedirs(folder_path)  # 创建文件夹  
    # i=0 
    # for index,item in enumerate(items):  
    #     if i<5:         
    #         html = requests.get(item.get('src'))   # get函数获取图片链接地址，requests发送访问请求  
    #         img_name = folder_path + str(index + 1) +'.jpg'  
    #         with open(img_name, 'wb') as file:  # 以byte形式将图片数据写入  
    #             file.write(html.content)  
    #             file.flush()  
    #         file.close()  # 关闭文件  
    #         print('第%d张图片下载完成' %(index+1))  
    #         time.sleep(1)  # 自定义延时  
    #         i=i+1


    return json.dumps(data1,ensure_ascii=False,indent=2)



run(host='localhost', port='8088', debug='TRUE')