/*************************************************************************
	> File Name: main.cc
	> Author: Kang
	> Mail:likang@tju.edu.cn 
	> Created Time: 2017年08月25日 星期五 10时49分45秒
 ************************************************************************/
#include "Pointer.h"
#include "SmartPointer.h"
struct Point{
	int x;
	int y;
	Point(){ std::cout << "Point() called." << std::endl; }
	Point( int xx, int yy ) : x(xx), y(yy) { std::cout << "Point(int,int)" << std::endl; }
	~Point(){ std::cout << "~Point() called." << std::endl; }
};

void test_Pointer(){

	Pointer<Point> p;
	Pointer<Point> p1(new Point());

	p1->x = 5;
	p1->y = 3;
}

void test_SmartPointer1(){
	
	SmartPointer<Point> p1( new Point(3, 4) );
	std::cout << p1->x << "," << p1->y << std::endl;
	
	SmartPointer<Point> p2(p1);
	std::cout << p2->x << "," << p2->y << std::endl;
	std::cout << "p1 use count :" << p1.use_count() <<std::endl;
	std::cout << "p2 use count :" << p2.use_count() <<std::endl;
	
	SmartPointer<Point> p3( new Point(7, 8) );
	std::cout << p3->x << "," << p3->y << std::endl;

	p2 = p3;
	std::cout << p2->x << "," << p2->y << std::endl;

	SmartPointer<int> pp( new int(3) );
	std::cout << *pp << std::endl;
}

void test_SmartPointer2(){
	
	SmartPointer<Point> p1( new Point(3,4) );
	if( p1 ){
		std::cout << p1->x << "," << p1->y << std::endl;
	}
	Point* p2 = new Point(3,4);
	Point* p3 = p1.get();

	if( p1 == p2 ) 
		std::cout << "p1==p2" << std::endl;
	if( p1 != p2 )
		std::cout << "p1!=p2" << std::endl;
	
	if( p1 == p3 ) 
		std::cout << "p1==p3" << std::endl;
	if( p1 != p3 )
		std::cout << "p1!=p3" << std::endl;

	SmartPointer<Point> p4(p1);
	if( p1 == p4 ) 
		std::cout << "p1==p4" << std::endl;
	if( p1 != p4 )
		std::cout << "p1!=p4" << std::endl;

	SmartPointer<Point> p5(new Point(7,8));
	if( p1 == p5 ) 
		std::cout << "p1==p5" << std::endl;
	if( p1 != p5 )
		std::cout << "p1!=p5" << std::endl;
}

int main(void){
	test_SmartPointer2();
	return 0;
} 
