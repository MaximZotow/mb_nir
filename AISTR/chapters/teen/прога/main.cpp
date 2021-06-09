#include<funcs.cpp>



int main(int argc, char *argv[])
{
    QElapsedTimer timer;
    timer.start();
    QCoreApplication a(argc, argv);
    default_random_engine generator;
    normal_distribution<double> distribution(0,2);

    double H = 30;
    double L = 100;
    double fi_pi = 5;//tut
    double fi = fi_pi*M_PI/180;
    double d = 40;//tut
    double r = 145e-12;

    double left_down_angle = qAtan(d*qCos(fi)/(2*(H-d/2*qSin(fi))));
    double right_down_angle = qAtan(d*qCos(fi)/(2*(H+d/2*qSin(fi))));
    qDebug() << right_down_angle*180/M_PI << "right_down";

    double left_down_dlina = d*qCos(fi)/(2*(qSin(left_down_angle)));
    double right_down_dlina = d*qCos(fi)/(2*(qSin(right_down_angle)));
    qDebug() << right_down_dlina << "right_down_dlina";
    double left_up_dlina = sqrt(pow(d/2,2)+pow(L,2)+pow(H,2)-2*sqrt(pow(d,2)/4+pow(L,2))*H*qCos(M_PI-fi-qAtan(d/(2*L))));
    double left_up_angle = qAcos(-(pow(d,2)/4+pow(L,2)-pow(left_up_dlina,2)-pow(H,2))/(2*H*left_up_dlina));
    double rigth_up_dlina = sqrt(pow(d/2,2)+pow(L,2)+pow(H,2)-2*sqrt(pow(d,2)/4+pow(L,2))*H*qCos(M_PI+fi-qAtan(d/(2*L))));
    double right_up_angle = qAcos(-(pow(d,2)/4+pow(L,2)-pow(rigth_up_dlina,2)-pow(H,2))/(2*H*rigth_up_dlina));


    //левая сторона
    double eps_left = qAsin(left_down_dlina*2*qSin(left_down_angle)/d);
//    double inter_left=dlina(left_down_angle,left_down_dlina,eps_left,fi_rasp);
    //правая сторона
//    double eps_right = qAsin(right_down_dlina*2*qSin(right_down_angle)/d);
    double eps_right = M_PI-eps_left;
//    double inter_right = dlina(right_down_angle,right_down_dlina,eps_right,fi_rasp);

//    qDebug() << dlina(right_down_angle,right_down_dlina,eps_right,right_up_angle)<< "max l";
//    qDebug() << dlina(left_down_angle,left_down_dlina,eps_left,left_up_angle)<< "max l";

//    qDebug() <<"leftup" << left_up_angle;
//    qDebug() <<"riup" << right_up_angle;
//    qDebug() <<"lefdo" << left_down_angle;
//    qDebug() <<"rido" << right_down_angle;
\



    QString filename;
    filename = "H = " + QString::number(H)+ " d = " + QString::number(d) + ".txt";
    QFile right_file("rigth_file.txt");
    QTextStream right_data(&right_file);
    //cout << filename.toStdString();
    QFile left_file(filename);
//    QFile left_file("testfile.txt");
    QTextStream left_data(&left_file);
    QFile test("test.xls");
    QTextStream data(&test);
    map<int, value> right_values;
    map<int, value> left_values;
    right_file.open(QIODevice::WriteOnly);
    left_file.open(QIODevice::WriteOnly);
    test.open(QIODevice::WriteOnly);
    for (int j = 0; j < 10000000; ++j)
    {
        double buff = distribution(generator);
        while (qAbs(buff) > 1) {
            buff = distribution(generator);
        }
//            double buff = box_muller();
            if (j%1000000 == 0)
                qDebug() << j/1000000 <<"/10";
        if (qAsin(buff)>-right_down_angle && qAsin(buff)<-right_up_angle)
        {
            double rh = dlina(right_down_angle,right_down_dlina,eps_right,qAsin(qAbs(buff)));
            right_values[address(rh)].i++;
            right_values[address(rh)].vec.push_back(rh);
//            data << rh << "\n";
        }
        else if (qAsin(buff)<left_down_angle && qAsin(buff)>left_up_angle)
        {

            double lh = dlina(left_down_angle,left_down_dlina,eps_left,qAsin(buff));
//            qDebug()<< left_down_angle << " "<< qAsin(buff) << " " << left_up_angle<< " "<< lh;
            left_values[address(lh)].i++;
            left_values[address(lh)].vec.push_back(lh);
//            data << lh << "\n";
        }
    }
//    cout << values;
    for (const auto& amount:left_values) {
        left_data << /*%i.first << " *** " <<*/amount.second.i*2*r*pow(10,6)/10 << "\n";
    }
    left_data<< "sep" << "\n"<<"\n";
    for (const auto& amount:right_values) {
        left_data /*<< qAbs(i.first) << " *** " */<< amount.second.i*2*r*pow(10,6)/10 << "\n";
    }

    qDebug() << "KONCHILOS'";
    qDebug() << "time " << double(timer.elapsed()/double(1000));
    right_file.close();
    left_file.close();
    test.close();
    return 0;
}

