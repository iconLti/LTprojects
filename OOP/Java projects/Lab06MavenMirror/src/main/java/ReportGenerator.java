import net.sf.jasperreports.engine.*;
import net.sf.jasperreports.engine.data.JRXmlDataSource;
import net.sf.jasperreports.engine.util.JRLoader;

import java.io.File;
import java.util.HashMap;

public class ReportGenerator {
    public static void generatePDFReport() throws JRException {
        String sourceFileName = "C:\\Users\\User\\JaspersoftWorkspace\\MyReports\\ClinicPDF.jasper";
        String xmlDataSource = "C:\\Users\\User\\Desktop\\LETI\\II\\OOP\\Java projects\\MainDocs\\AZ1.xml";

        // Загрузка скомпилированного файла отчета
        JasperReport jasperReport = (JasperReport) JRLoader.loadObject(new File(sourceFileName));

        // Создание источника данных из XML
        JRXmlDataSource dataSource = new JRXmlDataSource(new File(xmlDataSource), "/patients/patient");

        // Параметры отчета (если требуются)
        HashMap<String, Object> parameters = new HashMap<>();

        // Заполнение отчета
        JasperPrint jasperPrint = JasperFillManager.fillReport(jasperReport, parameters, dataSource);
        // Экспорт в PDF
        JasperExportManager.exportReportToPdfFile(jasperPrint, "C:\\Users\\User\\JaspersoftWorkspace\\MyReports\\GeneratedReport.pdf");
    }

    public static void generateHTMLReport() throws JRException {
        String sourceFileName = "C:\\Users\\User\\JaspersoftWorkspace\\MyReports\\ClinicHTML.jasper";
        String xmlDataSource = "C:\\Users\\User\\Desktop\\LETI\\II\\OOP\\Java projects\\MainDocs\\AZ1.xml";

        // Загрузка скомпилированного файла отчета
        JasperReport jasperReport = (JasperReport) JRLoader.loadObject(new File(sourceFileName));

        // Создание источника данных из XML
        JRXmlDataSource dataSource = new JRXmlDataSource(new File(xmlDataSource), "/patients/patient");

        // Параметры отчета (если требуются)
        HashMap<String, Object> parameters = new HashMap<>();

        // Заполнение отчета
        JasperPrint jasperPrint = JasperFillManager.fillReport(jasperReport, parameters, dataSource);
        // Экспорт в HTML
        JasperExportManager.exportReportToHtmlFile(jasperPrint, "C:\\Users\\User\\JaspersoftWorkspace\\MyReports\\GeneratedReport.html");
    }
}
