#include "threadcontroller.h"

ThreadController::ThreadController(QObject *p){
    threadPool = new QThreadPool();
    threadPool->setExpiryTimeout(60*1000*3); //设置一个thread多少时间内没有使用，自动过期
    threadPool->setMaxThreadCount(5); //设置最大的活跃线程

    QObject::connect(this,&ThreadController::sendResult,this,&ThreadController::recieveResult);
}
ThreadController::~ThreadController(){
    threadPool->clear();
    threadPool->releaseThread();  //释放线程
    QObject::connect(this,&QObject::destroyed,threadPool,&QObject::deleteLater);
}


void ThreadController::execTask(int a,int b){
    Task *task = new Task(this,a,b);
    task->setAutoDelete(true);  //设置自动删除标志位
    //当用 threadPool 执行 task 后， threadPool 接管 task 的销毁，执行完后会自动删除 task 对象
    //如果想要重复使用一个 QRunnable 对象 ，将自动删除标志位设为 false,并且用 tryStart() 方法来执行
    threadPool->start(task,0);

}

//SLOT
void ThreadController::recieveResult(int result){
    emit calResult(result);
}

bool allowEven(const int &p){
    return p%2==0;
}
bool allowOdd(const int &p){
    return p%2==1;
}
void sum(int &result, const int &value){
    result+=value;
}
int multi(const int &a, const int &b){
    return a*b;
}
void multi2(int &a, const int &b){
    if(a==0)a=1;
    a*=b;
}

int ThreadController::execAsync(int a,int b){
    QList<int> list;
    for(int i=0;i<10;i++){
        list<<i;
    }

    QList<int> newArray = QtConcurrent::blockingFiltered(list,allowOdd);
    qDebug()<<"过滤后的值 :"<<newArray;

    int result = QtConcurrent::blockingFilteredReduced(list,allowOdd,sum);
    qDebug()<<"0-10奇数累加值 :"<<result;

    qDebug()<<"reduce后的list :"<<list;
    int result2 = QtConcurrent::blockingFilteredReduced(list,allowOdd,multi2);
    qDebug()<<"0-10奇数累乘值 :"<<result2;

    QFuture<int> calSum = QtConcurrent::run(multi,a,b);
    return calSum.result();
}


