#include <iostream>
#include <vector>

using namespace std;

class Dice {
public:
    int face_number;
    vector<double> probability; 

    Dice(int Face_number, vector<double> Probability) {
        double tmp = 1;
        if (Face_number < 4)
            face_number = 2;
        else if (Face_number < 6)
            face_number = 4;
        else if (Face_number < 8)
            face_number = 6;
        else if (Face_number < 12)
            face_number = 8;
        else if (Face_number < 20)
            face_number = 12;
        else face_number = 20;

        for (int i = 0; i < face_number; i++) {
            if (i == face_number - 1 || Probability[i] > tmp) {
                probability.emplace_back(tmp);
                tmp = 0;
            } else {
                probability.emplace_back(Probability[i]);
                tmp -= Probability[i];
            }


        }
    }
};

class DiceSet {
public:
    DiceSet(vector<Dice> vec) {
        elements = vec;
    }

    int min_sum() {
        return elements.size();
    }

    int max_sum() {
        int res = 0;
        for (auto &e:elements)
            res += e.face_number;
        return res;
    }

    vector<double> sum_probabilities() { 
        if (elements.empty()) return {};
        int min = min_sum();
        int max = max_sum();
        int curr_size = 0;

        std::vector<double> sub_res, tmp, res;
        for (int i = 0; i < max; i++) {
            res.emplace_back(0);
        }
        tmp = sub_res = res;

        curr_size = elements[0].face_number;
        for (int i = 0; i < elements[0].face_number; i++)
            tmp[i] = elements[0].probability[i];

        for (unsigned int i = 1; i < elements.size(); i++) {
            sub_res = res;
            for (int j = 0; j < elements[i].face_number; j++) {
                for (int k = 0; k < curr_size; k++) {
                    sub_res[j + k + 1] += elements[i].probability[j] * tmp[k];
                }
            }
            curr_size += elements[i].face_number;
            tmp = sub_res;
        }

        res.clear();
        for (int i = min - 1; i < max; i++) {
            res.emplace_back(sub_res[i]);
        }

        return res;
    }

    void print_sum_probabilities() {
        vector<double> tmp = sum_probabilities();
        for (int i = 0; i <= max_sum() - min_sum(); i++) {
            std::cout << i + min_sum() << ":  " << tmp[i] << std::endl;
        }
    }

    double  expected_value() {
        double res = 0;
        vector<double> tmp = sum_probabilities();
        int i = min_sum();
        for (auto &e:tmp) {
            res += e * (i++);
        }
        return res;
    }
};

ostream &operator<<(ostream &os, DiceSet &obj) {
    for (auto &e: obj.elements) os << e << std::endl;
    return os;
}

bool operator<(DiceSet &obj_l, DiceSet &obj_r) {
    return obj_l.expected_value() < obj_r.expected_value();
}

bool operator>(DiceSet &obj_l, DiceSet &obj_r) {
    return obj_r < obj_l;
}

bool operator<=(DiceSet &obj_l, DiceSet &obj_r) {
    return !(obj_l > obj_r);
}

bool operator>=(DiceSet &obj_l, DiceSet &obj_r) {
    return !(obj_l < obj_r);
}

bool operator==(DiceSet &obj_l, DiceSet &obj_r) {
    return !(obj_l < obj_r) && !(obj_l > obj_r);
}

bool operator!=(DiceSet &obj_l, DiceSet &obj_r) {
    return !(obj_l == obj_r);
