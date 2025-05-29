import java.util.LinkedList;
import java.util.Queue;

public class Fila {
    private final Queue<Integer> fila = new LinkedList<>();

    public synchronized void adicionar(int item) {
        fila.add(item);
        notifyAll();
    }

    public synchronized int remover() throws InterruptedException {
        while (fila.isEmpty()) {
            wait();
        }
        return fila.poll();
    }
}
