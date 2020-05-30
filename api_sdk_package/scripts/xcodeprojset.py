#!/usr/bin/python
# -*- encoding: utf-8 -*-
import sys
import os
import subprocess
import xml.etree.ElementTree as ET

def get_Node(rootNode, tag, key):
	rlt = rootNode
	iterator = rootNode.iter()

	if tag != "":
		iterator = rootNode.iter(tag)

	for node in iterator:
#		print "get_Node : " + node.text
		if node.text == key:
			rlt = node
			break
	return rlt


def get_Next(rootNode, node):
	iterator = rootNode.iter()

	for curNode in iterator:
		if curNode == node:
			return next(iterator)

def add_Node(node, key, value):
	tmpKey = ET.SubElement(node, "key")
	tmpKey.text = key
	tmpVal = ET.SubElement(node, "string")
	tmpVal.text = value


def main(argv):
	bAddIdxStoreOpt = True	# 기본값이 true
	bAddStdLibOpt = False	# option에 따라 달라짐
	bAddCompilerOpt = False	# option에 따라 달라짐

	cwd = os.getcwd()
	projectName = sys.argv[1]
	projectPath = projectName + ".xcodeproj"
	pbxprojPath = projectPath + "/project.pbxproj"
	tmpPbxPath = projectPath + "/tmp.pbxproj"
	absPath = cwd + "/" + pbxprojPath

	if os.path.exists(absPath) == False:
		print "'" + absPath + "'" + " is not exists."
		return

	print "xcode project setting - " + absPath

	# option을 확인한다.
	for option in sys.argv:
		if option == '-addDefine':
			bAddCompilerOpt = True
		elif option == '-addStdlib':
			bAddStdLibOpt = True

	# 기존 pbxproj파일을 xml로 컨버트하기
	subprocess.call(['plutil','-convert','xml1',absPath,'-o',tmpPbxPath])

	top = ET.parse(tmpPbxPath).getroot()
	root = top.find("dict")

	# object 리스트 노드를 얻어오고
	objectsNode = get_Next(root, get_Node(root, "key", "objects"))
	# rootObj ID를 얻어오고
	rootObj = get_Next(root, get_Node(root, "key", "rootObject"))
	# rootObj ID를 이용해서 rootObj Node를 얻어오고
	rootObjNode = get_Next(objectsNode, get_Node(objectsNode, "key", rootObj.text))
	# 위에서 얻어온 rootObjNode에서 buildConfigurationList가 있는 노드의 ID를 얻어오고
	bcListNode = get_Next(rootObjNode, get_Node(rootObjNode, "key", "buildConfigurationList"))
	# 위에서 얻어온 build configuration list node id로 build configuration node를 얻어오고
	bcNode = get_Next(objectsNode, get_Node(objectsNode, "key", bcListNode.text))
	# 위에서 얻은 Node에서 debug / release config node의 ID가 있는 Node를 얻어오고
	arrNode = get_Next(bcNode, get_Node(bcNode, "key", "buildConfigurations"))

	# 필요한 플래크 추가하고
	for configNodeID in arrNode.iter("string"):
		configNode = get_Next(objectsNode, get_Node(objectsNode, "key", configNodeID.text))
		bsNode = get_Next(configNode, get_Node(configNode, "key", "buildSettings"))

		if bAddIdxStoreOpt == True:
			add_Node(bsNode, "COMPILER_INDEX_STORE_ENABLE", "NO")

		if bAddCompilerOpt == True:
			add_Node(bsNode, "CC", "/opt/llvm38/bin/clang")
			add_Node(bsNode, "CXX", "/opt/llvm38/bin/clang++")

		if bAddStdLibOpt == True:
			add_Node(bsNode, "CLANG_CXX_LANGUAGE_STANDARD", "c++11")
			add_Node(bsNode, "CLANG_CXX_LIBRARY", "libc++")

	# 저장하고
	tree = ET.ElementTree(top)
	tree.write(open(projectPath + '/tmp.xml', 'w'), encoding='utf-8')

	# 임시 파일 삭제하고 
	if os.path.exists(tmpPbxPath):
		os.remove(tmpPbxPath)

	if os.path.exists(absPath):
		os.remove(absPath)

	# 컨버트해서 다시 집어넣기
	subprocess.call(['plutil','-convert','xml1',projectPath + '/tmp.xml','-o',absPath])

	# 임시 파일 삭제
	if os.path.exists(projectPath + '/tmp.xml'):
		os.remove(projectPath + '/tmp.xml')


if __name__ == "__main__":
        main(sys.argv[1:])

