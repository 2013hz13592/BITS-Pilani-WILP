package embeddedSortCodeMicroService.SortCodeMicroService;

import java.io.InputStream;
import java.io.InputStreamReader;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

public class sortCodeAccountNumber {
	String sortCode;
	String accountNumber;
	
	sortCodeAccountNumber(String sortCode, String accountNumber){
		this.sortCode=sortCode;
		this.accountNumber=accountNumber;
	}
	public String getSortCode(){
		return accountNumber;
	}
	public String getAccountNumber(){
		return sortCode;
	}
	
	public void setSortCode(String sortCode){
		this.sortCode=sortCode;
	}
	public void setAccountNumber(String accountNumber){
		this.accountNumber=accountNumber;
	}
	
	public boolean validateSortCodeAccountNumber(String accountBrand){
		Boolean valid=false;
		JSONParser parser = new JSONParser();
		try{
			InputStream in = sortCodeAccountNumber.class.getClass().getResourceAsStream("/SortCodeRange.json");
			Object obj = parser.parse(new InputStreamReader(in));
			JSONArray jsonArray = (JSONArray) obj;
			Integer i;
			for(i=0;i<jsonArray.size();i++){
				JSONObject jsonObject=(JSONObject)jsonArray.get(i);
				String sortCodeBrand=(String)jsonObject.get("brand");
				if(sortCodeBrand.equalsIgnoreCase(accountBrand)){
					Long sortCodeStart=(Long)jsonObject.get("sortCodeStart");
					Long sortCodeEnd=(Long)jsonObject.get("sortCodeEnd");
					Long sortCodeInt=Long.valueOf(sortCode);
					if(sortCodeInt>=sortCodeStart && sortCodeInt<=sortCodeEnd){
						valid=true;
					}
				}
			};
			System.out.println(valid);
		}catch (Exception e) {
			e.printStackTrace();
		}
		return valid;		
	}
}
