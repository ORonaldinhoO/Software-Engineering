#!/usr/bin/env python
# -*- coding: UTF-8 -*-
"""
@Project ：document_similarity
@File    ：main.py
@Author  ：Ray
@Date    ：2021/9/17 17:58
@Function：
"""

import jieba
from simhash import Simhash
import re
import sys
from memory_profiler import profile


# 读取文本
# @profile
def read_txt(txt_loc):
    """
    :param txt_loc: 文件路径
    :return: 读取得到的文本字符串
    """
    doc = ''
    with open(txt_loc, "r", encoding='utf-8') as f:
        for line in f.readlines():
            line = line.strip('\n')  # 去掉列表中每一个元素的换行符
            line = line.strip(' ')  # 去除空字符
            # print(line)
            doc += line  # 字符串拼接
        # print(doc)
        f.close()  # 关闭文件

    return doc


# 写入文本
# @profile
def write_txt(txt_loc, content):
    """
    :param txt_loc:写入文件路径
    :param content:写入内容
    :return: 返回去掉html的纯净文本
    """
    with open(txt_loc, "a", encoding='utf-8') as f:
        f.write(content)
        f.close()  # 关闭文件


# 利用正则表达式，去除html格式
# @profile
def filter_html(html):
    """
    :param html: html
    :return: 返回去掉html的纯净文本
    """
    dr = re.compile(r'<[^>]+>', re.S)  # 正则表达式
    dd = dr.sub('', html).strip(' ')
    dd = dd.split()  # split后得到列表
    # print(dd)
    doc = ''
    for d in dd:
        d = d.strip()
        doc += d  # 字符串拼接

    return doc


# 求两篇文章相似度
# @profile
def simhash_similarity(text1, text2):
    """
    :param text1: 文本1
    :param text2: 文本2
    :return: 返回两篇文章的相似度
    """
    aa_simhash = Simhash(text1)
    bb_simhash = Simhash(text2)

    max_hashbit = max(len(bin(aa_simhash.value)), (len(bin(bb_simhash.value))))
    print("max hashbit: " + str(max_hashbit))

    similar = 0
    # 判断分母为0
    if max_hashbit:
        # 汉明距离
        distance = aa_simhash.distance(bb_simhash)
        print("汉明距离：" + str(distance))
        # 计算重合率
        similar = 1 - distance / max_hashbit

    return round(similar, 2)


# 命令行传参/程序内输入传参，并实现全部查重功能
# @profile
def cmd(write_path='check_out_all.txt'):
    """
    :param write_path: 写入文件的路径
    """
    try:
        prm = sys.argv  # 接受命令行传入的参数
        print('参数列表：', str(prm))
        path1 = prm[1]
        path2 = prm[2]
        write_path = prm[3]
        # 下两行注释代码在非命令行传参时使用
        # path1 = input("原版论文：")  # 例如：test_sample1\orig.txt
        # path2 = input("待检测的论文：")  # 例如：test_sample1\orig_0.8_dis_1.txt
        text1 = read_txt(path1)
        text2 = read_txt(path2)
        # print('去除html格式前的文本：')
        # print(text1)
        # print(text2)

        text1 = filter_html(text1)
        text2 = filter_html(text2)
        # print("\nfilter_html:")
        # print(text1)
        # print(text2)

        # jieba库分词
        text1 = jieba.lcut(text1, cut_all=True)
        text2 = jieba.lcut(text2, cut_all=True)
        similar = simhash_similarity(text1, text2)
        result = '原论文路径：' + path1 + '\n' \
                 + '检测论文路径：' + path2 + '\n' \
                 + '重合率：' + str(similar) + '\n\n'
        print(result)
        write_txt(write_path, result)

    except IndexError:
        print("输入错误")
    except FileNotFoundError:
        print("找不到文件，请再度确认")
    except Exception as e:
        print(f"Unknown Error:{e}")


if __name__ == '__main__':
    cmd()
