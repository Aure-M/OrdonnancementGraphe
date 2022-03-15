import java.util.ArrayList;

import Files.FileProcessing;
import Graphes.Graphe;
import Graphes.Node;

public class Test {
    public static void main(String[] args) {
        ArrayList<Node> nodes= FileProcessing.readFile("test.txt");
        Graphe g = new Graphe(nodes);
        g.afficheMatrice();
        g.detectionCircuit();

        System.out.println(g.detectionCircuit());

    }

}
