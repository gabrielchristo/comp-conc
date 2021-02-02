class Buffer {
    static final int N = 5; //tamanho do buffer
    private int[] buffer = new int[N];
    private int count = 0, in = 0, out = 0;

    // Construtor
    Buffer() {
        for (int i = 0; i < N; i++)
            buffer[i] = 0;
    }

    //Metodo para retornar tamanho do buffer
    public Integer size()
    {
        return this.buffer.length;
    }


    public synchronized void Insere(int elemento) {
        try {
            while (count == N) {
                wait();
            }
            buffer[in] = elemento;
            in = (in + 1) % N;
            count++;
            notifyAll();
        } catch (InterruptedException e) {
        }
    }


    public synchronized int Remove() {
        int elemento;
        try {
            while (count == 0) {
                wait();
            }
            elemento = buffer[out % N];
            out = (out + 1) % N;
            count--;
            notifyAll();
            return elemento;
        } catch (InterruptedException e) {
            return -1;
        }
    }


}

