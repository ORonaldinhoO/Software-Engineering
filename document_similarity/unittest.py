#!/usr/bin/env python
# -*- coding: UTF-8 -*-
"""
@Project ：document_similarity
@File    ：unittest.py
@Author  ：Ray
@Date    ：2021/9/18 23:15
@Function：
"""

import jieba
from simhash import Simhash
import re

# 读取文本
def read_txt(txt_loc):
    """
    :param txt_loc: 文件路径
    :return: 读取得到的文本字符串
    """
    doc = ''
    with open(txt_loc, "r", encoding='utf-8') as f:
        for line in f.readlines():
            line = line.strip('\n')  # 去掉列表中每一个元素的换行符
            line = line.strip(' ')
            # print(line)
            doc += line
        # print(doc)
        f.close()  # 关闭文件

    return doc


# 写入文本
def write_txt(txt_loc, content):
    """
    :param txt_loc:写入文件路径
    :param content:写入内容
    :return: 返回去掉html的纯净文本
    """
    with open(txt_loc, "a", encoding='utf-8') as f:
        f.write(content)
        f.close()  # 关闭文件


# 去除html格式
def filter_html(html):
    """
    :param html: html
    :return: 返回去掉html的纯净文本
    """
    dr = re.compile(r'<[^>]+>', re.S)
    dd = dr.sub('', html).strip(' ')
    dd = dd.split()
    # print(dd)
    doc = ''
    for d in dd:
        d = d.strip()
        doc += d

    return doc


# 求两篇文章相似度
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
    if max_hashbit:
        # 汉明距离
        distance = aa_simhash.distance(bb_simhash)
        print("汉明距离：" + str(distance))
        similar = 1 - distance / max_hashbit

    return round(similar, 2)


# 命令行传参/程序内输入传参，并实现全部查重功能
def cmd(write_path='unit_test.txt'):
    """
    :param write_path: 写入文件的路径
    """
    orig = 'test_sample1\orig.txt'  # 原版论文
    units = ['test_sample1\orig_0.8_add.txt', 'test_sample1\orig_0.8_del.txt', 'test_sample1\orig_0.8_dis_1.txt',
             'test_sample1\orig_0.8_dis_10.txt', 'test_sample1\orig_0.8_dis_15.txt','test_sample2\orig_0.8_add.txt',
             'test_sample2\orig_0.8_del.txt', 'test_sample2\orig_0.8_dis_1.txt', 'test_sample2\orig_0.8_dis_10.txt',
             'test_sample2\orig_0.8_dis_15.txt']  # 测试对象，包括两个文件夹下对应的测试样本
    try:
        text1 = read_txt(orig)
        text1 = filter_html(text1)
        text1 = jieba.lcut(text1, cut_all=True)

        count = 1
        for unit in units:
            print(count)
            # path1 = input("原版论文：")      # 例如：test_sample1\orig.txt
            # path2 = input("待检测的论文：")   # 例如：test_sample1\orig_0.8_dis_1.txt

            text2 = read_txt(unit)
            # print('去除html格式前的文本：')
            # print(text1)
            # print(text2)

            text2 = filter_html(text2)
            # print("\nfilter_html:")
            # print(text1)
            # print(text2)

            text2 = jieba.lcut(text2, cut_all=True)
            similar = simhash_similarity(text1, text2)
            result = str(count) + '\n原论文路径：' + orig + '\n' \
                     + '检测论文路径：' + unit + '\n' \
                     + '重合率：' + str(similar) + '\n\n'
            print(result)
            write_txt(write_path, result)
            count += 1

    except IndexError:
        print("输入错误")
    except FileNotFoundError:
        print("找不到文件，请再度确认")
    except Exception as e:
        print(f"Unknown Error:{e}")


if __name__ == '__main__':
    cmd()
