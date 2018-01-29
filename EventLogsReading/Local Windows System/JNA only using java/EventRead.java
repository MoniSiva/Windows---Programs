import java.util.*;
import java.net.*;
import java.sql.*;
import java.io.*;
import java.io.File;
import java.io.FileWriter;
import java.util.Map;
import java.util.TreeMap;
import java.lang.*;
import java.util.*;
import java.net.*;
import java.sql.*;
import java.io.*;
import java.text.*;
import java.util.Date;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import net.sf.jasperreports.engine.design.JasperDesign;
import net.sf.jasperreports.engine.xml.JRXmlLoader;
import net.sf.jasperreports.engine.*;
import net.sf.jasperreports.engine.util.*;
import net.sf.jasperreports.engine.JREmptyDataSource;
import net.sf.jasperreports.engine.JRException;
import net.sf.jasperreports.engine.JasperExportManager;
import net.sf.jasperreports.engine.JasperFillManager;
import net.sf.jasperreports.engine.JasperPrint;
import net.sf.jasperreports.engine.JRException; 
import net.sf.jasperreports.engine.JRExporterParameter; 
import net.sf.jasperreports.engine.JasperExportManager; 
import net.sf.jasperreports.engine.JasperFillManager;
import net.sf.jasperreports.engine.JasperPrint; 
import net.sf.jasperreports.engine.JasperPrintManager; 
import net.sf.jasperreports.engine.JasperRunManager;
import net.sf.jasperreports.engine.data.JRBeanArrayDataSource; 
import net.sf.jasperreports.engine.data.JRBeanCollectionDataSource; 
import net.sf.jasperreports.engine.data.JRTableModelDataSource; 
import net.sf.jasperreports.engine.export.JRCsvExporter;
import net.sf.jasperreports.engine.export.JRXlsExporter; 
import net.sf.jasperreports.engine.export.JRXlsExporterParameter; 
import net.sf.jasperreports.engine.util.JRLoader; 
import com.itextpdf.text.*;
import com.itextpdf.text.pdf.*;
import java.nio.charset.StandardCharsets;
import net.sf.jasperreports.engine.JREmptyDataSource;
import net.sf.jasperreports.engine.JRException;
import net.sf.jasperreports.engine.JRExporter;
import net.sf.jasperreports.engine.JRExporterParameter;
import net.sf.jasperreports.engine.JasperCompileManager;
import net.sf.jasperreports.engine.JasperExportManager;
import net.sf.jasperreports.engine.JasperFillManager;
import net.sf.jasperreports.engine.JasperPrint;
import net.sf.jasperreports.engine.JasperReport;
import net.sf.jasperreports.engine.export.JRPdfExporter;
import net.sf.jasperreports.engine.xml.JRGenericPrintElementParameterFactory.Parameter;
import net.sf.jasperreports.view.JasperViewer;


import net.sf.jasperreports.engine.*;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;

import com.sun.jna.platform.win32.Advapi32Util.Account;
import com.sun.jna.platform.win32.Advapi32Util.EventLogIterator;
import com.sun.jna.platform.win32.Advapi32Util.EventLogRecord;
import com.sun.jna.platform.win32.LMAccess.USER_INFO_1;
import com.sun.jna.platform.win32.WinNT.HANDLE;
import com.sun.jna.platform.win32.WinNT.HANDLEByReference;
import com.sun.jna.platform.win32.WinNT.PSID;
import com.sun.jna.platform.win32.WinNT.SECURITY_DESCRIPTOR_RELATIVE;
import com.sun.jna.platform.win32.WinNT.SID_NAME_USE;
import com.sun.jna.platform.win32.WinNT.WELL_KNOWN_SID_TYPE;
import com.sun.jna.platform.win32.WinReg.HKEY;
import com.sun.jna.platform.win32.WinReg.HKEYByReference;
public class EventRead{
	public static void main(String args[] ){
			int count;			
		EventLogIterator iter = new EventLogIterator("Application");
			 count=0;
			while(iter.hasNext()) {
				
				EventLogRecord record = iter.next();
				count++;
				System.out.println( "Event ID: " + record.getEventId()+ ", Event Type: " + record.getType()+ ", Event Source: " + record.getSource());
				
			}
			
			EventLogIterator iter1 = new EventLogIterator("Secutity");
			 count=0;
			while(iter1.hasNext()) {
				
				EventLogRecord record1 = iter1.next();
				count++;
				System.out.println( "Event ID: " + record1.getEventId()+ ", Event Type: " + record1.getType()+ ", Event Source: " + record1.getSource());
				
			}
			
			EventLogIterator iter2 = new EventLogIterator("System");
			 count=0;
			while(iter2.hasNext()) {
				
				EventLogRecord record2 = iter2.next();
				count++;
				System.out.println( "Event ID: " + record2.getEventId()+ ", Event Type: " + record2.getType()+ ", Event Source: " + record2.getSource());
				
			}
			
		
		
	}			
		
}
