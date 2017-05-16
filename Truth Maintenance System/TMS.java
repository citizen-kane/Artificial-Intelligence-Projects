import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

/**
 * Created by krishnaagarwala on 4/8/17.
 */

class FactRule{
    String start;
    boolean status;
    String rule;
}
class DepOrRule{
    String start;
    ArrayList<String> dependsUpon;
    ArrayList<String> rule;
    ArrayList<Boolean> status;
}

class DepAndRule{
    String start;
    ArrayList<String> dependsUpon;
    String rule;
    Boolean status;
}

class DepAndOrRule{
    String start;
    ArrayList<Boolean> typeAnd;
    List<List<String>> dependsUpon;
    ArrayList<String> rule;
    ArrayList<Boolean> status;
}

public class TMS {
    static HashMap<String, Integer> tellMap;
    static ArrayList<FactRule> ruleFactRule;
    static ArrayList<DepOrRule> ruleDepOrRule;
    static ArrayList<DepAndRule> ruleDepAndRule;
    static ArrayList<DepAndOrRule> ruleDepAndOrRule;

    public static void printResult(){
        checkAllRules2();
        checkAllRules();
        for (FactRule fr: ruleFactRule){
            System.out.println(fr.rule);
        }

        for(DepOrRule dor: ruleDepOrRule){
            boolean printFlag = false;
            boolean firstTime = true;
            String printString = dor.start+":";
            for(int i=0; i<dor.dependsUpon.size();i++){
                if(dor.status.get(i)==Boolean.TRUE){
                    printFlag = true;
                    if(firstTime){
                        printString = printString + dor.rule.get(i);
                        firstTime = false;
                    } else {
                        printString = printString + ", "+ dor.rule.get(i);
                    }
                }
            }
            if (printFlag){
                System.out.println(printString);
            }
        }

        for(DepAndRule dar: ruleDepAndRule){
            if (dar.status==Boolean.TRUE){
                System.out.println(dar.start+":"+dar.rule);
            }
        }
        for(DepAndOrRule daor: ruleDepAndOrRule){
            boolean printFlag = false;
            boolean firstTime = true;
            String printString = daor.start+":";
            for(int i=0; i<daor.rule.size();i++){
                if(daor.status.get(i)==Boolean.TRUE){
                    printFlag = true;
                    if(firstTime){
                        printString = printString+daor.rule.get(i);
                        firstTime = false;
                    } else {
                        printString = printString+", "+daor.rule.get(i);
                    }
                }
            }
            if(printFlag){
                System.out.println(printString);
            }
        }
    }
    public static void checkAllRules2(){
        for (DepOrRule dor: ruleDepOrRule){
            for(int i=0; i<dor.dependsUpon.size(); i++){
                if (tellMap.containsKey(dor.dependsUpon.get(i))) {
                    //dor.status.set(i, Boolean.TRUE);
                    if(!(tellMap.containsKey(dor.start))) {
                        //addAssertRule(dor.start);
                        tellMap.put(dor.start,1);
                    }
                } else {
                    //dor.status.set(i, Boolean.FALSE);
                }
            }
        }

        for(DepAndOrRule daor : ruleDepAndOrRule){
            boolean preflag = false;
            for(int i=0; i<daor.rule.size();i++){
                if(daor.typeAnd.get(i)==Boolean.FALSE){
                    if(tellMap.containsKey(daor.dependsUpon.get(i).get(0))) {
                        //daor.status.set(i, Boolean.TRUE);
                        preflag = true;
                    } else {
                        //daor.status.set(i, Boolean.FALSE);
                    }
                } else {
                    Boolean flag = Boolean.FALSE;
                    for(int j=0; j<daor.dependsUpon.get(i).size(); j++){
                        if(tellMap.containsKey(daor.dependsUpon.get(i).get(j))){
                            flag = Boolean.TRUE;
                        } else {
                            flag = Boolean.FALSE;
                            break;
                        }
                    }
                    daor.status.set(i, flag);
                    if(flag){
                        preflag = true;
                    }
                }
            }
            if(preflag){
                if(!(tellMap.containsKey(daor.start))){
                    //addAssertRule(daor.start);
                    tellMap.put(daor.start,1);
                }
            }
        }

        for (DepAndRule dar: ruleDepAndRule){
            Boolean flag = Boolean.FALSE;
            for(int i=0; i<dar.dependsUpon.size(); i++){
                if (tellMap.containsKey(dar.dependsUpon.get(i))){
                    flag = Boolean.TRUE;
                } else {
                    flag = Boolean.FALSE;
                    break;
                }
            }
            //dar.status = flag;
            if(flag){
                if(!(tellMap.containsKey(dar.start))){
                    //addAssertRule(dar.start);
                    tellMap.put(dar.start,1);
                }
            }
        }
    }

    public static void checkAllRules(){
        for (DepOrRule dor: ruleDepOrRule){
            for(int i=0; i<dor.dependsUpon.size(); i++){
                if (tellMap.containsKey(dor.dependsUpon.get(i))) {
                    dor.status.set(i, Boolean.TRUE);
                } else {
                    dor.status.set(i, Boolean.FALSE);
                }
            }
        }

        for(DepAndOrRule daor : ruleDepAndOrRule){
            for(int i=0; i<daor.rule.size();i++){
                if(daor.typeAnd.get(i)==Boolean.FALSE){
                    if(tellMap.containsKey(daor.dependsUpon.get(i).get(0))) {
                        daor.status.set(i, Boolean.TRUE);
                    } else {
                        daor.status.set(i, Boolean.FALSE);
                    }
                } else {
                    Boolean flag = Boolean.FALSE;
                    for(int j=0; j<daor.dependsUpon.get(i).size(); j++){
                        if(tellMap.containsKey(daor.dependsUpon.get(i).get(j))){
                            flag = Boolean.TRUE;
                        } else {
                            flag = Boolean.FALSE;
                            break;
                        }
                    }
                    daor.status.set(i, flag);
                }
            }
        }

        for (DepAndRule dar: ruleDepAndRule){
            Boolean flag = Boolean.FALSE;
            for(int i=0; i<dar.dependsUpon.size(); i++){
                if (tellMap.containsKey(dar.dependsUpon.get(i))){
                    flag = Boolean.TRUE;
                } else {
                    flag = Boolean.FALSE;
                    break;
                }
            }
            dar.status = flag;
        }
    }

    public static void addDependAndOrRule(String valueLeft, String valueRight){
        String[] valPart = valueLeft.split("\\+");
        DepAndOrRule daor = new DepAndOrRule();
        daor.typeAnd = new ArrayList<>();
        daor.dependsUpon = new ArrayList<>();
        daor.rule = new ArrayList<>();
        daor.status = new ArrayList<>();
        daor.start = valueRight;

        for(int i=0; i<valPart.length; i++){
            if (valPart[i].contains("*")){
                String[] valPart2 = valPart[i].split("\\*");
                String initial = "";
                daor.typeAnd.add(Boolean.TRUE);
                daor.status.add(Boolean.FALSE);
                for(int j=0; j<valPart2.length; j++){
                    initial=initial+valPart2[j]+",";
                }
                daor.dependsUpon.add(Arrays.asList(valPart2));
                daor.rule.add("{"+initial+valueLeft+"->"+valueRight+"}");
            } else {
                daor.typeAnd.add(Boolean.FALSE);
                daor.dependsUpon.add(Arrays.asList(valPart[i]));
                daor.rule.add("{"+valPart[i]+","+valueLeft+"->"+valueRight+"}");
                daor.status.add(Boolean.FALSE);
            }
        }
        ruleDepAndOrRule.add(daor);
    }


    public static void addDependAndRule(String valueLeft, String valueRight){
        DepAndRule dar = new DepAndRule();
        dar.dependsUpon = new ArrayList<>();
        dar.start = valueRight;

        String[] valPart = valueLeft.split("\\*");
        String initial="";

        for (int i = 0; i<valPart.length; i++){
            dar.dependsUpon.add(valPart[i]);
            initial = initial + valPart[i] + ",";
        }
        dar.rule = "{" + initial + valueLeft + "->" + valueRight + "}";
        dar.status = Boolean.FALSE;
        ruleDepAndRule.add(dar);
    }

    public static void addDependOrRule(String valueLeft, String valueRight){
        DepOrRule dor = new DepOrRule();
        dor.dependsUpon = new ArrayList<>();
        dor.rule = new ArrayList<>();
        dor.status = new ArrayList<>();
        dor.start = valueRight;

        String[] valPart = valueLeft.split("\\+");

        for (int i = 0; i<valPart.length; i++){
            dor.dependsUpon.add(valPart[i]);
            dor.rule.add("{"+valPart[i]+","+valueLeft+"->"+valueRight+"}");
            dor.status.add(Boolean.FALSE);
        }
        ruleDepOrRule.add(dor);
    }

    public static void addFactRule(String str1, String str2){
        FactRule fr = new FactRule();
        fr.start = str2;
        fr.status = true;
        fr.rule = str1+"->"+str2;
        ruleFactRule.add(fr);
    }
    public static void addAssertRule(String value){
        String repValue;
        if (value.substring(0,1).compareTo("-")==0){
            repValue = value.substring(1);
        } else {
            repValue = "-"+value;
        }
        if(tellMap.containsKey(repValue)){
            tellMap.remove(repValue);
        }
        int index = -1;
        for(int x = 0; x<ruleFactRule.size(); x++){
            if ((ruleFactRule.get(x).start.compareTo(repValue)==0) && (ruleFactRule.get(x).rule.compareTo(repValue)==0)){
                index = x;
            }
        }
        if (index!=-1) {
            ruleFactRule.remove(index);
        }

        tellMap.put(value,1);
        FactRule fr = new FactRule();
        fr.start = value;
        fr.status = true;
        fr.rule = value;
        ruleFactRule.add(fr);
    }
    public static void removeAssertRule(String value){
        if(tellMap.containsKey(value)){
            tellMap.remove(value);
        }
        int index = -1;
        for(int x = 0; x<ruleFactRule.size(); x++){
            //if ((ruleFactRule.get(x).start.compareTo(value)==0) && (ruleFactRule.get(x).rule.compareTo(value)==0)){
            if (ruleFactRule.get(x).rule.compareTo(value)==0){
                index = x;
            }
        }
        if (index!=-1) {
            ruleFactRule.remove(index);
        }
    }

    public static void processTell(String value){
        String[] valueParts;
        if(value.contains(">")){

            valueParts = value.split("->");
            addFactRule(valueParts[0], valueParts[1]);

            if (value.contains("*") && !value.contains("+")){
                addDependAndRule(valueParts[0], valueParts[1]);
            } else if (value.contains("+") && !value.contains("*")){
                addDependOrRule(valueParts[0], valueParts[1]);
            } else if(value.contains("+") && value.contains("*")){
                addDependAndOrRule(valueParts[0], valueParts[1]);
            } else if(!value.contains("+") && !value.contains("*")){
                addDependOrRule(valueParts[0], valueParts[1]);
            }
            checkAllRules();
        } else {
            addAssertRule(value);
            checkAllRules();
        }
    }
    public static void processRetract(String value){
        removeAssertRule(value);
        checkAllRules();
    }
    public static void main(String[] args){

        String fileName = "TMSInput.txt";
        File textFile = new File(fileName);
        Scanner in = null;
        try {
            in = new Scanner(textFile);
        }
        catch (FileNotFoundException e) {
            System.out.println("File not found.\n");;
        }
        tellMap = new HashMap<>();
        ruleFactRule = new ArrayList<>();
        ruleDepOrRule = new ArrayList<>();
        ruleDepAndRule = new ArrayList<>();
        ruleDepAndOrRule = new ArrayList<>();

        while (in.hasNext()){
            String value=in.next();
            if (value.matches("Tell(.*)")){
                value=value.substring(5); //value now contains string post Tell:
                processTell(value);
            } else {
                value=value.substring(8); //value now contains string post Retract:
                processRetract(value);
            }
        }
        in.close();
        printResult();
    }
}