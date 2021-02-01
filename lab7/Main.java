/*
 * Classe para modelar os elementos mannipulados pelos produtores e consumidores
 * */
class Product
{
    //Id do produto
    public Integer id;

    //Elemento do produto
    private Object element;

    //Construtor da classe
    public Product(Integer id)
    {
        this.element = new Object();
        this.id = id;
    }

    //Metodo para setar objeto no produto
    void setElement(Object newElement)
    {
        this.element = newElement;
    }

    //Metodo para imprimir produto
    public void print()
    {
        System.out.println("Elemento: " + this.id + "\tProduto: " + this.element.toString());
    }

}

/*
 * Classe para modelar o buffer que armazenara os produtos
 * */
class Buffer
{
    //Definindo vetor de produtos
    private Product[] productsVector;

    //Indice da posicao apropriada para se retirar/inserir produtos
    private Integer positionIndex;

    //Construtor da classe
    public Buffer(Integer sizeProductsVector)
    {
        this.productsVector = new Product[sizeProductsVector];
        this.positionIndex = 0;
    }

    //Metodo para retornar tamanho do buffer
    public Integer size()
    {
        return this.productsVector.length;
    }

    //Verifica se vetor esta vazio
    public synchronized boolean isEmpty()
    {
        return this.positionIndex == 0;
    }

    //Verifica se vetor esta cheio
    public synchronized boolean isFull()
    {
        return  this.positionIndex == this.productsVector.length;
    }

    //Metodo para inserir produtos dentro do buffer
    public synchronized void insert(Product product)
    {
        try
        {
            //Verificando se buffer nao esta cheio
            while(this.isFull())
                this.wait();

            //Inserindo produto na posicao apropriada
            this.productsVector[this.positionIndex] = product;

            //Atualizando indice do buffer
            this.positionIndex++;

            //Liberando as demais threads
            this.notifyAll();
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
            return;
        }
    }

    //Metodo para remover elementos do buffer
    public synchronized Product remove()
    {
        try
        {
            //Verificando se buffer nao esta vazio
            while(this.isEmpty())
                this.wait();

            //Atualizando indice do buffer
            this.positionIndex--;

            //Removendo produto na posicao apropriada
            Product product = this.productsVector[this.positionIndex];

            //Liberando as demais threads
            this.notifyAll();

            //Retornando elementos
            return  product;
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
            return null;
        }
    }

    //Metodo para imprimir elementos do buffer
    public void print()
    {
        System.out.println("=====");
        for(Product currentProduct : this.productsVector)
            currentProduct.print();
    }
}

/*
 * Classe com os recursos compartilhado entre as threads
 * */
class SharedResource
{
    //Buffer compartilhado entre as threads
    private Buffer buffer;

    //Quantidade de elementos que precisam ser criados
    public Integer numberTotalProduct;

    //Quantidade atual de elementos criados
    private Integer currentNumberProduct;

    //Construtor
    public SharedResource(Integer sizeBuffer,Integer numberTotalProduct)
    {
        this.buffer = new Buffer(sizeBuffer);
        this.numberTotalProduct = numberTotalProduct;
        this.currentNumberProduct = 0;
    }

    //Getter do campo de buffer
    public Buffer getBuffer()
    {
        return this.buffer;
    }

    //Getter para o campo currentNumberProduct
    public synchronized Integer getCurrentNumberProduct()
    {
        return this.currentNumberProduct;
    }

    //Metodo para atualizar o quantidade atual de produtos criados
    public synchronized void updateCurrentNumberProduct()
    {
        this.currentNumberProduct++;
    }
}

/*
 * Classe das threads Produtoras
 * */
class Producer extends Thread
{
    //Id do Produtor
    public Integer id;

    //Recurso Compartilhado
    private SharedResource sharedResource;

    //Construtor da classe
    public Producer(Integer id,SharedResource sharedResource)
    {
        this.id = id;
        this.sharedResource = sharedResource;
    }

    //Metodo para produzir um elemento
    private synchronized Product createProduct(Integer idProduct)
    {
        //Criando um produto
        Product product = new Product(idProduct);

        //Atualizando o numero de produtos criados
        this.sharedResource.updateCurrentNumberProduct();

        //Retornando o produto
        return product;
    }

    //Metodo executado pelas threads
    public void run()
    {
        //Iniciando a thread
        System.out.printf("Thread Produtora %d iniciada\n", this.id);

        //Produzindo os elementos necessarios
        while(this.sharedResource.getCurrentNumberProduct() != this.sharedResource.numberTotalProduct)
        {
            //Criando um produto
            Product product = this.createProduct(this.sharedResource.getCurrentNumberProduct());

            //Inserindo o produto no buffer
            this.sharedResource.getBuffer().insert(product);
        }

        //Encerrando a thread
        System.out.printf("Thread Produtora %d finalizada\n", this.id);
    }
}

/*
 * Classe das threads Consumidoras
 * */
class Consumer extends Thread
{
    //Id do Produtor
    public Integer id;

    //Recurso Compartilhado
    private SharedResource sharedResource;

    //Construtor da classe
    public Consumer(Integer id, SharedResource sharedResource)
    {
        this.id = id;
        this.sharedResource = sharedResource;
    }

    //Metodo para processar o produto
    private void processesProduct(Product product)
    {
        //Printando o produto
        product.print();
    }

    //Metodo executado pelas threads
    public void run()
    {
        //Iniciando a thread
        System.out.printf("Thread Consumidora %d iniciada\n", this.id);

        //Processando os elementos necessarios
        while((this.sharedResource.getCurrentNumberProduct() != this.sharedResource.numberTotalProduct)
        && (!this.sharedResource.getBuffer().isEmpty()))
        {
            //Pegando um produto do buffer
            Product product = this.sharedResource.getBuffer().remove();

            //Processando o produto
            this.processesProduct(product);
        }

        //Encerrando a thread
        System.out.printf("Thread Consumidora %d finalizada\n", this.id);
    }
}



/*
* Classe da funçao principal
* */
public class Main
{
    //Definindo variaveis
    static final Integer numberProduct = 30;
    static final Integer numberConsumer = 5;
    static final Integer numberProducer = 5;
    static final Integer sizeBuffer = 4;

    //Funcao principal
    public static void main(String[] args)
    {
        //Criando Produtores e consumidores
        Thread[] producer = new Thread[numberProducer];
        Thread[] consumer = new Thread[numberConsumer];

        //Criando recursos compartilhado entre as threads
        SharedResource sharedResource = new SharedResource(sizeBuffer,numberProduct);

        //Inicializando produtores
        for(int indexProducer = 0; indexProducer < producer.length; indexProducer++)
            producer[indexProducer] = new Producer(indexProducer,sharedResource);

        //Inicializando consumidores
        for(int indexConsumer = 0; indexConsumer < producer.length; indexConsumer++)
            consumer[indexConsumer] = new Consumer(indexConsumer,sharedResource);

        //Iniciando a execucao dos produtores
        for(int indexProducer = 0; indexProducer < producer.length; indexProducer++)
            producer[indexProducer].start();

        //Iniciando a execucao dos consumidores
        for(int indexConsumer = 0; indexConsumer < producer.length; indexConsumer++)
            consumer[indexConsumer].start();

        //Aguardando produtores terminarem
        for(int indexProducer = 0; indexProducer < producer.length; indexProducer++)
        {
            try
            {
                producer[indexProducer].join();
            } catch (InterruptedException e)
            {
                e.printStackTrace();
                return;
            }
        }

        //Aguardando consumidores terminarem
        for(int indexConsumer = 0; indexConsumer < consumer.length; indexConsumer++)
        {
            try
            {
                consumer[indexConsumer].join();
            } catch (InterruptedException e)
            {
                e.printStackTrace();
                return;
            }
        }

    }
}
