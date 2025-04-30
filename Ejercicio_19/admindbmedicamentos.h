#ifndef ADMINDBMEDICAMENTOS_H
#define ADMINDBMEDICAMENTOS_H

class AdminDB  {

private:
    static AdminDB * instancia;
    AdminDB();

public:
    static AdminDB * getInstancia();

    void conectar();
};

#endif // ADMINDBMEDICAMENTOS_H
