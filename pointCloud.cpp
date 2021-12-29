#include <iostream>
#include <exception>
#include <utility>

class Point {
public:
	Point() = default;
	Point(int v1, int v2, int v3) : x{v1}, y{v2}, z{v3} {}


	friend std::ostream& operator <<(std::ostream& out, const Point& p) {
		out<<"\n[ "<<p.x<<" "<<p.y<<" "<<p.z<<" ]\n";
		return out;
	}

	bool operator ==(const Point& p) const {
		return p.x == x && p.y == y && p.z == z;
	}

	Point operator +(const Point &p) const {
		Point temp;
		temp.x = x + p.x;
		temp.y = y + p.y;
		temp.z = z + p.z;
		return temp;
	}

private:
	int x, y, z;
};

class PointCloud {
public:
	PointCloud() = default;

	PointCloud(size_t n) : array{new Point[n]}, idx{}, size{n} {}

	~PointCloud() { delete []array;}

	void emplace_back(const Point &p) {
		if(idx >= size)
			throw std::exception{};

		array[idx++] = p;
	}

	friend std::ostream& operator <<(std::ostream& out, const PointCloud & p) {
		out<<"\n\nclass "<<typeid(p).name()<<" >> "<<&p<<" : \n";

		for(size_t i=0;i<p.idx;i++)
			out<<p.array[i];
		return out;
	}

	PointCloud(const PointCloud &p) : array{new Point[p.size]}, idx{p.idx}, size{p.size} {
		for(size_t i=0;i<p.idx;i++)
			array[i] = p.array[i];
	}

	PointCloud& operator =(const PointCloud &p) {
		delete [] array;

		array = new Point[p.size];
		idx = p.idx;
		size = p.size;

		for(size_t i=0;i<p.idx;i++)
			array[i] = p.array[i];

		return *this;
	}

	PointCloud(PointCloud &&p) : array{new Point[p.size]}, idx{p.idx}, size{p.size} {
		for(size_t i=0;i<p.idx;i++)
			array[i] = p.array[i];

		p.idx = 0;
		p.size = 0;
		p.array = nullptr;
		delete [] p.array;
	}

private:
	Point *array = nullptr;
	size_t idx, size;
};

int main() {
	Point p1(10, 20, 30);
	Point p2(11, 21, 31);

	PointCloud ptr{15};

	ptr.emplace_back(p1);
	ptr.emplace_back(p2);
	ptr.emplace_back(Point{100,200,300});
	ptr.emplace_back(Point{400, 500, 600});

	std::cout<<ptr<<"\n";

	PointCloud copyPtr = ptr;
	PointCloud movePtr(std::move(ptr));

	movePtr.emplace_back(Point{4,5,6});
	movePtr.emplace_back(Point{700, 800, 900});
	movePtr.emplace_back(Point{82, 83, 83});

	std::cout<<ptr<<"\n";
	std::cout<<copyPtr<<"\n";
	std::cout<<movePtr<<"\n";

}
