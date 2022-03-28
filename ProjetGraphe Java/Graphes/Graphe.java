package Graphes;

import java.util.ArrayList;

public class Graphe {
    private ArrayList<Boolean[]> matriceAdjacence;
    private ArrayList<Node> listNode = null;

    public Graphe(ArrayList<Node> listNode) {
        this.listNode = listNode;
        this.matriceAdjacence = new ArrayList<Boolean[]>();
        fillMatriceAdjacence();
    }

    private Graphe(Graphe g){
        this.listNode = g.getListNode();
        this.matriceAdjacence = new ArrayList<Boolean[]>();
        fillMatriceAdjacence();
    }
    private void fillMatriceAdjacence() {
        Boolean[] tab;
        for (Node n : listNode) {
            tab = new Boolean[listNode.size()];
            for (int i = 0; i < tab.length; i++) {
                tab[i]=false;
            }
            matriceAdjacence.add(tab);
        }

        for (Node n : listNode) {
            for (int constraint : n.getContraintes()) {
                matriceAdjacence.get(constraint-1)[n.getId()-1] = true;
            }
        }
    }
    public ArrayList<Node> getListNode() {
        ArrayList<Node> copy = new ArrayList<Node>();
        for (Node n : listNode) {
            copy.add(n);
        } 
        return copy;
    }

    public void afficheMatrice() {

        Boolean[] tmp;
        System.out.print("-----------MATRICE D'ADJACENCE----------\n\n");
        String spaces=listNode.size()>10? "   ": "  ";
        System.out.print(spaces); 
        for (int i = 0; i < listNode.size(); i++) {
            System.out.print(listNode.get(i).getId()+" ");
        }
        System.out.print("\n");
        for (int i = 0; i < listNode.size(); i++) {
            Node actualNode=listNode.get(i);
            tmp=matriceAdjacence.get(i);
            spaces=actualNode.getId()>=10? " ": "  ";
            
            System.out.print(actualNode.getId()+spaces);
            for (int j = 0; j < tmp.length; j++) {
                if (tmp[j] == false) {
                    System.out.print("X ");   
                } else {
                    System.out.print("\033[1;31m"+"O "+"\033[0m");
                }
            }
            System.out.print("\n");
        }
        System.out.print("\n---------------------------------------\n\n");
    }

    public ArrayList<Node> detectPointEntree(){
        ArrayList<Node> result = new ArrayList<Node>();
        for (Node node : listNode) {
            if (node.getContraintes().size()==0){
                result.add(node);
            }
        }
        return result;
    }
    public ArrayList<Node> detectPointSortie(){
        ArrayList<Node> result = new ArrayList<Node>();
        for (Node node : listNode) {
            Boolean isAnEndPoint = true;
            for (int i = 0; i < listNode.size(); i++) {
                Boolean [] line = matriceAdjacence.get(i);
                if(line[node.getId()-1]==true){
                    isAnEndPoint=false;
                    break;
                }
            }
            if (isAnEndPoint) {
                result.add(node);
            }
        }
        return result;
    }
    public Boolean detectionCircuit(){

        ArrayList<Node> nodes=this.getListNode();

        ArrayList<Node> endAndEntryPoints= new ArrayList<Node>();
        
        while (nodes.size()<=1) {
            Graphe tmp = new Graphe(nodes);

            for (Node node : tmp.detectPointEntree()) {
                endAndEntryPoints.add(node);
            }
            for (Node node : tmp.detectPointSortie()) {
                endAndEntryPoints.add(node);
            }
    
            if(endAndEntryPoints.size()==0)
                return true;
    
            for (Node node : endAndEntryPoints) {
                nodes.remove(node);
            }
    
            endAndEntryPoints.clear();        
        }
        return false;
    }
}
