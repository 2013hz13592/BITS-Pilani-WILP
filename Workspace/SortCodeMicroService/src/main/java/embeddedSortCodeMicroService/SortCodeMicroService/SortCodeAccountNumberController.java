package embeddedSortCodeMicroService.SortCodeMicroService;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class SortCodeAccountNumberController {
	
    @RequestMapping(value="/SortCodeAccountNumber",method=RequestMethod.GET)
    public boolean SortCodeValidator(@RequestParam(value="sortCode", defaultValue="000000") String sortCode, 
    								@RequestParam(value="accountNumber", defaultValue="000000") String accountNumber,
    								@RequestParam(value="accountBrand", defaultValue="RBS") String accountBrand) 
    {
    	sortCodeAccountNumber SortCodeValidatorObj=new sortCodeAccountNumber(sortCode, accountNumber);
    	return(SortCodeValidatorObj.validateSortCodeAccountNumber(accountBrand));
    }
}
