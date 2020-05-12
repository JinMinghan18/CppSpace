#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
/*����*/
class P {
public:
    P() {};
    P(double x, double y) :X(x), Y(y) {}
    void print() {
        cout << "(" << X << "," << Y << ")";
    }
    void set(double x, double y) {
        X = x;
        Y = y;
    }
    double X;
    double Y;
};

/*��������*/
class FX {
public:
    FX(int x, int y) : row(x), cols(y) {
        matrix = new double* [row];
        for (int i = 0; i < row; i++)
            matrix[i] = new double[cols];
        con = new double[row];
        solution = new double[row];
    }
    FX(int x, int y, double** fx, double* c) {
        row = x;
        cols = y;
        matrix = fx;
        con = c;
        solution = new double[row];
    }
    ~FX() {
        for (int i = 0; i < row; i++)
            delete[] matrix[i];
        delete[] matrix;
        delete[] con;
        delete[] solution;
    }
    void set() {
        cout << "Input the EquationSet:\n";
        double temp;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> temp;
                matrix[i][j] = temp;
            }
            cin >> temp;
            con[i] = temp;
        }
    }
    void print() {
        cout << "Print the EquationSet:\n";
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < cols; j++)
                cout << left << setprecision(5) << setw(7) << matrix[i][j] << " ";
            cout << "  " << left << setprecision(5) << setw(7) << con[i] << endl;
        }
        cout << endl << endl;
    }
    void printAnswer() {
        cout << "Print the answer:\n";
        for (int i = 0; i < row; i++)
            cout << "[x" << i + 1 << "]= " << solution[i] << endl;
    }
    bool columnElimination() {                               //����Ԫ��˹��Ԫ��
        int* js = new int[row];                             //�洢��Ԫ�������кŵ�����
        for (int k = 0; k < row - 1; k++) {                    //ѡ��Ԫ��
            int is;                                         //��Ԫ�������к�
            double max = 0;                                 //����Ԫ�ص����ֵ
            for (int i = k; i < row; i++)
                for (int j = k; j < row; j++) {
                    double t = fabs(matrix[i][j]);
                    if (t > max) {
                        max = t;
                        js[k] = j;
                        is = i;
                    }
                }
            if (max == 0) {                                  //���ֵ������0��det����0�������޽�
                delete[] js;
                return false;
            }
            else {                                           //ͨ�����н���������Ԫ�ؽ�������k�е�k����
                if (js[k] != k)                             //�б任
                    for (int i = 0; i < row; i++)
                        swap(matrix[i][k], matrix[i][js[k]]);
                if (is != k)                                //�б任
                    for (int j = k; j < row; j++) {
                        swap(matrix[is][j], matrix[k][j]);
                        swap(con[k], con[is]);
                    }
            }
            for (int k = 0; k < row; k++) {                  //��ȥ����
                double major = matrix[k][k];
                for (int j = k; j < row; j++)
                    matrix[k][j] /= major;
                con[k] /= major;
                for (int i = k + 1; i < row; i++) {
                    double first = matrix[i][k];
                    bool flag = true;
                    for (int j = k; j < row; j++) {
                        matrix[i][j] -= first * matrix[k][j];
                        if (fabs(matrix[i][j]) > 1e-26)
                            flag = false;
                    }
                    if (flag)
                        return false;
                    con[i] -= first * con[k];
                }
            }
        }
        double d = matrix[row - 1][row - 1];                   //�ش�����
        solution[row - 1] = con[row - 1] / d;
        for (int i = row - 2; i >= 0; i--) {
            double t = 0.0;
            for (int j = i + 1; j <= row - 1; j++)
                t += matrix[i][j] * solution[j];
            solution[i] = con[i] - t;
        }
        js[row - 1] = row - 1;                              //���һ�������Ԫ���Ǳ���
        for (int k = row - 1; k >= 0; k--)                  //������ԭ������λ�õı仯�������λ�ù�λ
            if (js[k] != k) swap(solution[k], solution[js[k]]);
        delete[] js;
        return true;
    }
    double* getSolution() {                                  //ע�����ﷵ��һ��new�����飬֮����Ҫ����
        double* s = new double[row];
        for (int i = 0; i < row; i++)
            s[i] = solution[i];
        return s;
    }
private:
    int row;
    int cols;
    double** matrix;
    double* con;
    double* solution;
};

/*����ʽ��*/
class equation {
public:
    ~equation() {
        // delete[] factor;
    }
    void set(double* f, int l) {
        factor = f;
        length = l;
    }
    void print() {
        bool flag = true;
        cout << "f(x)=";
        for (int i = 0; i < length; i++) {
            if (factor[i] != 0) {
                if (flag == false) {
                    cout << " + ";
                }
                if (i != length - 1) {
                    cout << factor[i] << " " << "X^" << length - i - 1;
                }
                else {
                    cout << factor[length - 1];
                }
                flag = false;
            }
        }
        if (flag) {
            cout << 0;
        }
        cout << endl;
    }
    double solve(double x) {
        double sum = 0.0;
        for (int i = 0; i < length; i++) {
            sum += factor[i] * pow(x, length - i - 1);
        }
        return sum;
    }
    int length;
    double* factor;
};

/*�������*/
double convolution_operation(P* p, equation fk, equation fj, int n) {
    double sum = 0;
    // cout<<"\nfk\n    ";
    // fk.print();
    // cout<<"\nfj\n    ";
    // fj.print();
    for (int i = 0; i < n; i++) {
        // cout<<"\nx  "<<p[i].X;
        // cout<<"\nfk  "<<fk.solve(p[i].X)<<"  fj  "<<fj.solve(p[i].X);
        sum += fk.solve(p[i].X) * fj.solve(p[i].X);
        // cout<<"\n  sum  "<<sum<<endl;
    }
    // cout<<endl;
    return sum;
}
double convolution_operation(P* p, equation fk, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        // cout<<"\nfk  "<<fk.solve(p[i].X)<<"  y  "<<p[i].Y;
        sum += fk.solve(p[i].X) * p[i].Y;
        // cout<<"\n  sum  "<<sum<<endl;
    }
    // cout<<endl;    
    return sum;
}

/*���ζ���ʽ���*/
equation quadraticFitting(P* p, int num) {
    double factor2[3] = { 1,0,0 };
    double factor1[2] = { 1,0 };
    double factor0[1] = { 1 };
    equation f[3];
    f[2].set(factor0, 1);
    f[1].set(factor1, 2);
    f[0].set(factor2, 3);
    double** mat = new double* [3];
    for (int i = 0; i < 3; i++)
        mat[i] = new double[3];
    double* con = new double[3];

    for (int k = 0; k < 3; k++) {
        for (int j = 0; j < 3; j++) {
            mat[k][j] = convolution_operation(p, f[k], f[j], num);
        }
        con[k] = convolution_operation(p, f[k], num);
    }
    FX equS(3, 3, mat, con);
    equS.columnElimination();
    double* solution = equS.getSolution();
    equation yx;
    yx.set(solution, 3);
    return yx;
}

/*���ζ���ʽ���*/
equation cubicFitting(P* p, int num) {
    double factor3[4] = { 1,0,0,0 };
    double factor2[3] = { 1,0,0 };
    double factor1[2] = { 1,0 };
    double factor0[1] = { 1 };
    equation f[4];
    f[3].set(factor0, 1);
    f[2].set(factor1, 2);
    f[1].set(factor2, 3);
    f[0].set(factor3, 4);
    double** mat = new double* [4];
    for (int i = 0; i < 4; i++)
        mat[i] = new double[4];
    double* con = new double[4];

    for (int k = 0; k < 4; k++) {
        for (int j = 0; j < 4; j++) {
            mat[k][j] = convolution_operation(p, f[k], f[j], num);
        }
        con[k] = convolution_operation(p, f[k], num);
    }
    FX equS(4, 4, mat, con);
    equS.columnElimination();
    double* solution = equS.getSolution();
    equation yx;
    yx.set(solution, 4);
    return yx;
}

/*����͵�*/
P getLowestPoint(equation p) {
    P point;
    if (p.length == 3) {
        double a = p.factor[0];
        double b = p.factor[1];
        double c = p.factor[2];
        if (a > 0) {
            if (-b / (2 * a) < 1) {
                point.set(1, p.solve(1));
            }
            else if (-b / (2 * a) > 10) {
                point.set(10, p.solve(10));
            }
            else {
                point.set(-b / (2 * a), p.solve(-b / (2 * a)));
            }
        }
        else {
            if (-b / (2 * a) < 1) {
                point.set(10, p.solve(10));
            }
            else if (-b / (2 * a) > 10) {
                point.set(1, p.solve(1));
            }
            else {
                if (p.solve(10) > p.solve(1))
                    point.set(1, p.solve(1));
                else
                    point.set(10, p.solve(10));
            }
        }
    }
    else if (p.length == 4) {
        double a = p.factor[0];
        double b = p.factor[1];
        double c = p.factor[2];
        double d = p.factor[3];
        double t = 4 * b * b - 12 * a * c;
        if (a > 0) {
            if (t > 0) {
                double x1 = (-2 * b + sqrt(t)) / (6 * a);
                double x2 = (-2 * b - sqrt(t)) / (6 * a);
                point.set(x1, p.solve(x1));
                return point;
            }
            else {
                point.set(1, p.solve(1));
            }
        }
        else {
            if (t > 0) {
                double x1 = -2 * b + sqrt(t) / (6 * a);
                double x2 = -2 * b - sqrt(t) / (6 * a);
                point.set(x1, p.solve(x1));
                return point;
            }
            else {
                point.set(10, p.solve(10));
                return point;
            }
        }
    }
    else
    {
        cout << "Can not be resolved.";
    }
    return point;
}

int main() {
    int num;
    cout << "�������ܵ���\n   >>>";
    cin >> num;
    P* p = new P[num];
    cout << "������xֵ\n   >>>";
    for (int i = 0; i < num; i++)
        cin >> p[i].X;
    cout << "������yֵ\n   >>>";
    for (int i = 0; i < num; i++)
        cin >> p[i].Y;
    equation q_yx = quadraticFitting(p, num);
    cout << "���ζ���ʽ\n   >>>";
    q_yx.print();
    cout << "������͵�\n   >>>";
    P q_pnt;
    q_pnt = getLowestPoint(q_yx);
    q_pnt.print(); cout << endl;

    equation c_yx = cubicFitting(p, num);
    cout << "���ζ���ʽ\n   >>>";
    c_yx.print();
    cout << "������͵�\n   >>>";
    P c_pnt;
    c_pnt = getLowestPoint(c_yx);
    c_pnt.print(); cout << endl;
    delete[] c_yx.factor;
    delete[] q_yx.factor;
    delete[] p;
    getchar(); getchar();
}
