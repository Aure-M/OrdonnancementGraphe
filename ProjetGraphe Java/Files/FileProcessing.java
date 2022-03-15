package Files;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

import Graphes.Node;

public class FileProcessing {

    static public ArrayList<Node> readFile(String path) {
        ArrayList<Node> nodes= new ArrayList<Node>();
        try {
            BufferedReader rd = new BufferedReader(new FileReader(path));
            String line = "";
            String[] datas;
            Node tmpNode;
            while ((line = rd.readLine()) != null) {
                datas=line.split(" ");
                tmpNode= new Node(Integer.parseInt(datas[0]),Integer.parseInt(datas[1]));
                for (int i = 2; i < datas.length; i++) {
                    tmpNode.addContraintes(Integer.parseInt(datas[i]));
                }
                nodes.add(tmpNode);
            }
            rd.close();
            return nodes;
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return null;
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        }

    }
}