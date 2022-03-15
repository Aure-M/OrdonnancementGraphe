package Graphes;

import java.util.ArrayList;

public class Node {
    private int id;
    private int duree;
    private ArrayList<Integer> contraintes;

    public Node(int id, int duree){
        this.id=id;
        this.duree=duree;
        this.contraintes= new ArrayList<Integer>();
    }

    public int getId() {
        return id;
    }


    public int getDuree() {
        return duree;
    }

    public void addContraintes(int constaintID){
        contraintes.add(constaintID);
    }

    public ArrayList<Integer> getContraintes() {
        ArrayList<Integer> copy= new ArrayList<Integer>();
        for (Integer id : contraintes) {
            copy.add(id);
        }
        
        return copy;
    }
}
