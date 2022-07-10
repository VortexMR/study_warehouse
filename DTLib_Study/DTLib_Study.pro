QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    DTLib/DTString.cpp \
    DTLib/Exception.cpp \
    DTLib/Object.cpp

HEADERS += \
    DTLib/Array.h \
    DTLib/BTree.h \
    DTLib/BTreeArray.h \
    DTLib/BTreeNode.h \
    DTLib/CircleList.h \
    DTLib/DTString.h \
    DTLib/DualCircleList.h \
    DTLib/DualEndQueue.h \
    DTLib/DualLinkList.h \
    DTLib/DynamicArray.h \
    DTLib/DynamicHeap.h \
    DTLib/DynamicList.h \
    DTLib/DynamicMatrix.h \
    DTLib/Exception.h \
    DTLib/Graph.h \
    DTLib/GTree.h \
    DTLib/GTreeNode.h \
    DTLib/Heap.h \
    DTLib/LinkList.h \
    DTLib/LinkQueue.h \
    DTLib/LinkStack.h \
    DTLib/LinuxList.h \
    DTLib/List.h \
    DTLib/ListGraph.h \
    DTLib/Matrix.h \
    DTLib/MatrixGraph.h \
    DTLib/Object.h \
    DTLib/Pointer.h \
    DTLib/Queue.h \
    DTLib/RangeArray.h \
    DTLib/SeqList.h \
    DTLib/SharedPointer.h \
    DTLib/SmartPointer.h \
    DTLib/Sort.h \
    DTLib/Stack.h \
    DTLib/StaticArray.h \
    DTLib/StaticHeap.h \
    DTLib/StaticLinkList.h \
    DTLib/StaticList.h \
    DTLib/StaticMatrix.h \
    DTLib/StaticQueue.h \
    DTLib/StaticStack.h \
    DTLib/Tree.h \
    DTLib/TreeNode.h
