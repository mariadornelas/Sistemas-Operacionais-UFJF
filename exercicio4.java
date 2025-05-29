import java.util.LinkedList;
import java.util.Queue;

public class BlockingQueue<T> {
    private final Queue<T> queue = new LinkedList<>();
    private final int maxSize;

    public BlockingQueue(int maxSize) {
        this.maxSize = maxSize;
    }

    public synchronized void put(T item) throws InterruptedException {
        while (queue.size() == maxSize) {
            wait();
        }
        queue.add(item);
        System.out.println("Adicionado: " + item);
        notifyAll();
    }

    public synchronized T take() throws InterruptedException {
        while (queue.isEmpty()) {
            wait();
        }
        T item = queue.poll();
        System.out.println("Removido: " + item);
        notifyAll();
        return item;
    }
}

public class Main {
    public static void main(String[] args) {
        BlockingQueue<Integer> fila = new BlockingQueue<>(3);

        new Thread(() -> {
            for (int i = 1; i <= 10; i++) {
                try {
                    fila.put(i);
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        }).start();

        new Thread(() -> {
            for (int i = 1; i <= 10; i++) {
                try {
                    fila.take();
                    Thread.sleep(150);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            }
        }).start();
    }
}
