#include"BST.cpp"

int main()
{
	BST<int> testtree;
	int node[10]={23,11,56,5,20,30,89,77,45,50};
	for(int i=0;i<10;i++)
	{
		testtree.add(node[i]);
	}
	testtree.graph(std::cout);
	cout<<endl;
	cout<<"ǰ�����:"<<endl;
	testtree.frontorder(std::cout);
	cout<<endl;
	cout<<"�������:"<<endl;
	testtree.inorder(std::cout);
	cout<<endl;
	cout<<"�������:"<<endl;
	testtree.lastorder(std::cout);
	cout<<endl;
	cout<<"��α���:"<<endl;
	testtree.floor(std::cout);
	cout<<endl;
	testtree.ver_graph(std::cout);
	testtree.free();
}
