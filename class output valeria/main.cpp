//
//  main.cpp
//  class output valeria
//
//  Created by Valeria  Bukova on 21.11.2024.
//

#include <iostream>
using namespace std;


class IOutput {
public:
    virtual void Show() const = 0;
    virtual void Show(const char* info) const = 0;
    virtual ~IOutput() = default;
};


class IMath {
public:
    virtual int Max() const = 0;
    virtual int Min() const = 0;
    virtual float Avg() const = 0;
    virtual bool Search(int valueToSearch) const = 0;
    virtual ~IMath() = default;
};


class ISort {
public:
    virtual void SortAsc() = 0;
    virtual void SortDesc() = 0;
    virtual void SortByParam(bool isAsc) = 0;
    virtual ~ISort() = default;
};


class Array : public IOutput, public IMath, public ISort {
private:
    int* data;
    int size;

public:
    
    Array(const int* inputData, int inputSize) : size(inputSize) {
        data = new int[size];
        for (int i = 0; i < size; i++) {
            data[i] = inputData[i];
        }
    }

    
    ~Array() {
        delete[] data;
    }

    
    void Show() const override {
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    void Show(const char* info) const override {
        // Печатаем строку вручную
        for (const char* p = info; *p != '\0'; p++) {
            cout << *p;
        }
        cout << ": ";
        Show();
    }

   
    int Max() const override {
        int maxValue = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i] > maxValue) {
                maxValue = data[i];
            }
        }
        return maxValue;
    }

    int Min() const override {
        int minValue = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i] < minValue) {
                minValue = data[i];
            }
        }
        return minValue;
    }

    float Avg() const override {
        if (size == 0) return 0;
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += data[i];
        }
        return static_cast<float>(sum) / size;
    }

    bool Search(int valueToSearch) const override {
        for (int i = 0; i < size; i++) {
            if (data[i] == valueToSearch) {
                return true;
            }
        }
        return false;
    }

    
    void SortAsc() override {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    swap(data[j], data[j + 1]);
                }
            }
        }
    }

    void SortDesc() override {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (data[j] < data[j + 1]) {
                    swap(data[j], data[j + 1]);
                }
            }
        }
    }

    void SortByParam(bool isAsc) override {
        if (isAsc) {
            SortAsc();
        } else {
            SortDesc();
        }
    }

private:
    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }
};


int main() {
    
    int arrData[] = {5, 3, 8, 1, 9, 7};
    Array arr(arrData, 6);
    cout << "Testing IOutput:" << endl;
    arr.Show();
    arr.Show("Array elements");

    cout << "\nTesting IMath:" << endl;
    cout << "Max: " << arr.Max() << endl;
    cout << "Min: " << arr.Min() << endl;
    cout << "Avg: " << arr.Avg() << endl;
    cout << "Search for 8: " << (arr.Search(8) ? "Found" : "Not Found") << endl;
    cout << "Search for 10: " << (arr.Search(10) ? "Found" : "Not Found") << endl;

    cout << "\nTesting ISort:" << endl;
    arr.SortAsc();
    arr.Show("Sorted Ascending");
    arr.SortDesc();
    arr.Show("Sorted Descending");
    arr.SortByParam(true);
    arr.Show("Sorted By Param (Ascending)");
    arr.SortByParam(false);
    arr.Show("Sorted By Param (Descending)");

    return 0;
}
