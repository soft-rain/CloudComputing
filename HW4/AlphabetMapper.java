import java.io.IOException;
import java.util.StringTokenizer;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapred.MapReduceBase;
import org.apache.hadoop.mapred.Mapper;
import org.apache.hadoop.mapred.OutputCollector;
import org.apache.hadoop.mapred.Reporter;

public class AlphabetMapper extends MapReduceBase implements Mapper<LongWritable, Text, Text, IntWritable> {
   public void map(LongWritable key, Text value, OutputCollector<Text, IntWritable> output, Reporter reporter) throws IOException{

   String line = value.toString();
   String resstr = line.toLowerCase();
   
   String match = "[^\uAC00-\uD7A3xfe0-9a-zA-Z\\s]";
   resstr = resstr.replace(" ",  "");
   resstr = resstr.replaceAll(match, "");
//   StringTokenizer tokenizer = new StringTokenizer(line);
   String  tokenizer[] = resstr.split("");    
   for(String Chars : tokenizer)  
   {  
       Text ckey = new Text(Chars);  
       IntWritable One = new IntWritable(1);  
       output.collect(ckey, One);                 
   }  
   }
}