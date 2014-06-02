#ifndef _KNN_H_
#define _KNN_H_
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <iterator>
#include <iostream>
using namespace std;

struct valueAndIndices{
	double value;
	int index;
};

int cmp(const valueAndIndices& a, const valueAndIndices& b){
	if (a.value < b.value)
		return 1;
	else
		return 0;
}

class data{
public:
	vector<double> _data;
	char _label;
	data();
	data(const data&);
};

data::data(){
	//copy(istream_iterator<double>(cin), istream_iterator<double>(), back_inserter(_data));
	double tmp;
	cin >> _label;
	cout << "请输入数据维数: ";
	int num;
	cin >> num;
	while (num--){
		cin >> tmp;
		_data.push_back(tmp);
	}
}

data::data(const data& d){
	_label = d._label;
	_data = d._data;
}

class trainingDataSet{
public:
	vector<data> _dataSet;
	vector<char> _labelSet;
	trainingDataSet();
};

trainingDataSet::trainingDataSet(){
	cout << "有多少组数据: ";
	int num;
	cin >> num;
	while (num--){
		data tempData;
		_dataSet.push_back(tempData);
		_labelSet.push_back(tempData._label);
	}
}

class kNN{
	data _testData;
	trainingDataSet _trainingDataSet;	
public:
	kNN();
	kNN(data aTestData, trainingDataSet aTrainingDataSet) : _testData(aTestData), _trainingDataSet(aTrainingDataSet){}
	vector<double> distances();
	vector<int> sortDistancesIndices(vector<double>);
	map<char, int> classCount(vector<int>, int);
	char classify(const map<char, int>&);
};

vector<double> kNN::distances(){
	vector<double> retVec;
	double sum = 0, aDistance;
	for (vector<data>::const_iterator it1 = _trainingDataSet._dataSet.begin(); it1 != _trainingDataSet._dataSet.end(); ++it1){
		for (vector<double>::const_iterator it2 = _testData._data.begin(), it3 = it1->_data.begin(); it2 != _testData._data.end(); ++it2){
			sum += (*it2 - *it3) * (*it2 - *it3);
			++it3;
		}
		aDistance = sqrt(sum);
		retVec.push_back(aDistance);
		sum = 0;
	}
	return retVec;
}

vector<int> kNN::sortDistancesIndices(vector<double> vec){
	vector<int> retVec;
	vector<valueAndIndices> vecTemp;
	for (vector<double>::size_type st = 0; st != vec.size(); ++st){
		valueAndIndices v;
		v.value = vec[st];
		v.index = st;
		vecTemp.push_back(v);
	}
	sort(vecTemp.begin(), vecTemp.end(), cmp);
	for (vector<valueAndIndices>::const_iterator it = vecTemp.begin(); it != vecTemp.end(); ++it)
		retVec.push_back(it->index);
	return retVec;
}

map<char, int> kNN::classCount(vector<int> vec, int k){
	map<char, int> retMap;
	for (vector<int>::size_type st = 0; st != k; ++st)
		++retMap[_trainingDataSet._labelSet[vec[st]]];
	return retMap;
}

char kNN::classify(const map<char, int>& m){
	char labelResult;
	int num;
	map<char, int>::const_iterator baseIt = m.begin();
	num = baseIt->second;
	labelResult = baseIt->first;
	for (map<char, int>::const_iterator it = m.begin(); it != m.end(); ++it){
		if (it->second > num){
			num = it->second;
			labelResult = it->first;
		}
	}
	return labelResult;
}

#endif // !_KNN_H_
