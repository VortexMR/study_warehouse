/*
 * This file is part of the DTLib template project, http://www.dt4sw.com
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 唐佐林 (Delphi Tang)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <iostream>
#include "DTLib/DTString.h"
#include "DTLib/StaticArray.h"
#include "DTLib/DynamicArray.h"
#include "DTLib/DynamicList.h"
#include "DTLib/LinkList.h"
#include "DTLib/LinkStack.h"
#include "DTLib/LinkQueue.h"
#include "DTLib/BTree.h"
#include "DTLib/ListGraph.h"
#include "DTLib/SmartPointer.h"
#include "DTLib/SharedPointer.h"
#include "DTLib/Sort.h"
#include "DTLib/StaticMatrix.h"
#include "DTLib/DynamicMatrix.h"
#include "DTLib/BTreeArray.h"

using namespace DTLib;
using namespace std;

void ArrayDemo()
{
    cout << "ArrayDemo(): " << endl;

    double arr[] = { 0.5, 0.2, 0.3, 0.4, 0.1 };
    int len = sizeof(arr)/sizeof(*arr);

    StaticArray<double, 10> sa;
    DynamicArray<double> da;

    da.resize(len);

    for(int i=0; i<len; i++)
    {
        sa[i] = arr[i];
        da[i] = arr[i];
    }

    cout << "StaticArray: " << endl;

    for(int i=0; i<sa.length(); i++)
    {
        cout << sa[i] << endl;
    }

    cout << "DynamicArray: " << endl;

    for(int i=0; i<da.length(); i++)
    {
        cout << da[i] << endl;
    }
}

void ListDemo()
{
    cout << "ListDemo(): " << endl;

    LinkList<double> list;
    DynamicList<double> dl(50);

    for(int i=0; i<10; i++)
    {
        dl.insert(i/10.0);
    }

    dl.remove(5);
    
    for(int i=0; i<dl.length(); i++)
    {
        list.insert(dl[i]);
    }

    for(list.move(0); !list.end(); list.next())
    {
        cout << list.current() << endl;
    }
}

void StackQueueDemo()
{
    cout << "StackQueueDemo(): " << endl;

    LinkStack<int> stack;
    LinkQueue<int> queue;

    for(int i=0; i<10; i++)
    {
        stack.push(i);
        queue.add(i);
    }

    cout << "Stack: " << endl;

    while( stack.size() )
    {
        cout << stack.top() << endl;

        stack.pop();
    }

    cout << "Queue: " << endl;

    while( queue.length() )
    {
        cout << queue.front() << endl;

        queue.remove();
    }
}

void BinTreeDemo()
{
    cout << "BinTreeDemo(): " << endl;

    BTree<int> bt; // empty tree
    BTreeNode<int>* node = NULL;
    
    // construct binary tree
    bt.insert(1, NULL); // 1 is tree root

    node = bt.root();
    bt.insert(2, node); // 2 is left child of 1
    bt.insert(3, node); // 3 is right child of 1

    node = bt.find(2);
    bt.insert(4, node, RIGHT); // 4 is right child of 2
    bt.insert(5, node, LEFT);  // 5 is left child of 2

    node = bt.find(3);
    bt.insert(6, node, RIGHT); // 6 is right child of 3

    cout << "After construct: " << endl;
    cout << "Height: " << bt.height() << endl;
    cout << "Count: " << bt.count() << endl;
    cout << "Degree: " << bt.degree() << endl;

    cout << "BFS to access node value: " << endl;

    for(bt.begin(); !bt.end(); bt.next())
    {
        cout << bt.current() << endl;
    }

    bt.remove(2); // remove sub tree from node 2

    cout << "After remove: " << endl;
    cout << "Height: " << bt.height() << endl;
    cout << "Count: " << bt.count() << endl;
    cout << "Degree: " << bt.degree() << endl;

    cout << "BFS to access node value: " << endl;

    for(bt.begin(); !bt.end(); bt.next())
    {
        cout << bt.current() << endl;
    }
}

void BTreeArrayDemo()
{
    BTreeArray<char> bt(3);  // max height is 3
    int node = 1;

    // insert 'A' as root
    bt.set(node, 'A');

    cout << "length: " << bt.length() << endl;
    cout << "count: " << bt.count() << endl;
    cout << "height: " << bt.height() << endl;
    cout << "toplimit: " << bt.toplimit() << endl;

    node = bt.find('A');
    bt.set(bt.left(node), 'B');  // left child of 'A'
    bt.set(bt.right(node), 'C'); // right child of 'A'

    node = bt.find('C');
    bt.set(bt.left(node), 'F');  // left child of 'C'
    bt.set(bt.right(node), 'G'); // right child of 'C'

    bt.resize(4);  // max height is 4

    cout << "length: " << bt.length() << endl;
    cout << "count: " << bt.count() << endl;
    cout << "height: " << bt.height() << endl;
    cout << "toplimit: " << bt.toplimit() << endl;

    // use bin tree as an array
    for(int i=1; i<=bt.length(); i++)
    {
        try
        {
            cout << bt[i] << endl;  // if no element at node i, throw an InvalidOperationException
        }
        catch(const Exception&)
        {

        }
    }
}

void GraphDemo()
{
    cout << "GraphDemo(): " << endl;

    ListGraph<char, float> graph;

    // construct graph
    graph.addVertex('A');  // 0
    graph.addVertex('B');  // 1
    graph.addVertex('C');  // 2 
    graph.addVertex('D');  // 3
    graph.addVertex('E');  // 4

    graph.setEdge(0, 1, 0.2);  // v0->v1, weight: 0.2
    graph.setEdge(0, 4, 1.0);  // v0->v4, weight: 1.0
    graph.setEdge(1, 2, 0.3);  // v1->v2, weight: 0.3
    graph.setEdge(1, 4, 0.7);  // v1->v4, weight: 0.7
    graph.setEdge(2, 0, 0.4);  // v2->v0, weight: 0.4
    graph.setEdge(2, 3, 0.4);  // v2->v3, weight: 0.4
    graph.setEdge(2, 4, 0.3);  // v2->v4, weight: 0.3
    graph.setEdge(3, 4, 0.5);  // v3->v4, weight: 0.5
    graph.setEdge(4, 2, 0.2);  // v4->v2, weight: 0.2

    SharedPointer< Array<int> > r = graph.dijkstra(0, 4, 0xFFFF);
    double d = 0;

    cout << graph.getVertex((*r)[0]);

    for(int i=1; i<r->length(); i++)
    {
        d += graph.getEdge((*r)[i-1], (*r)[i]);
        cout << " -> " << graph.getVertex((*r)[i]);
    }

    cout << endl;
    cout << "distance: " << d << endl;
}

void SortDemo()
{
    cout << "SortDemo(): " << endl;

    int arr[] = {3, 1, 2, 5, 4, 6};
    int len = sizeof(arr)/sizeof(*arr);

    cout << "min -> max: " << endl;

    Sort::Bubble(arr, len);

    for(int i=0; i<len; i++)
    {
        cout << arr[i] << endl;
    }

    cout << "max -> min: " << endl;

    Sort::Quick(arr, len, false);

    for(int i=0; i<len; i++)
    {
        cout << arr[i] << endl;
    }
}

void PointerDemo()
{
    cout << "PointerDemo(): " << endl;

    SmartPointer<int> p1;
    SmartPointer<int> p2;

    p1 = new int(1);
    p2 = p1;

    cout << "p1: " << (!p1.isNull() ? *p1 : -1) << endl;
    cout << "p2: " << (!p2.isNull() ? *p2 : -1) << endl;

    SharedPointer<int> pp1;
    SharedPointer<int> pp2;

    pp1 = new int(2);
    pp2 = pp1;

    cout << "pp1: " << (!pp1.isNull() ? *pp1 : -1) << endl;
    cout << "pp2: " << (!pp2.isNull() ? *pp2 : -1) << endl;
}

void MatrixDemo()
{
    cout << "MatrixDemo(): " << endl;

    StaticMatrix<double, 3, 6> sm;

    for(int i=0; i<sm.row(); i++)
    {
        for(int j=0; j<sm.col(); j++)
        {
            sm[i][j] = i * sm.col() + j;
        }
    }

    for(int i=0; i<sm.row(); i++)
    {
        for(int j=0; j<sm.col(); j++)
        {
            cout << sm[i][j] << " ";
        }

        cout << endl;
    }

    cout << endl;

    DynamicMatrix<float> dm(4, 4);

    // create echelon matrix
    for(int i=0; i<dm.row(); i++)
    {
        dm[i].resize(i+1);
    }

    int v = 1;

    for(int i=0; i<dm.length(); i++)
    {
        for(int j=0; j<dm[i].length(); j++)
        {
            dm[i][j] = v++;
        }
    }

    for(int i=0; i<dm.length(); i++)
    {
        for(int j=0; j<dm[i].length(); j++)
        {
            cout << dm[i][j] << " ";
        }

        cout << endl;
    }

    cout << endl;

    // resize matrix to 4x4
    dm.format();

    // init new matrix
    DynamicMatrix<float> nm = dm;

    for(int i=0; i<nm.length(); i++)
    {
        for(int j=0; j<nm[i].length(); j++)
        {
            cout << nm[i][j] << " ";
        }

        cout << endl;
    }
}

void StringDemo()
{
    const char* s = "DTLib";
    String hello = "Hello: ";
    String str;

    str.insert(hello);
    
    str += s;

    cout << str.str() << endl;

    int index = str.indexOf(s);

    cout << "sub string index: " <<  index << endl;
    cout << "sub string: " << str.sub(index).str() << endl;

    str.replace(s, "Delphi Tang");

    cout << str.str() << endl;
}

int main()
{
    StringDemo();
    // PointerDemo();
    // SortDemo();
    // ArrayDemo();
    // ListDemo();
    // StackQueueDemo();
    // BinTreeDemo();
    // GraphDemo();
    // MatrixDemo();

    return 0;
}
