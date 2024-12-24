import net.sf.jasperreports.engine.*;
import net.sf.jasperreports.engine.data.JRXmlDataSource;

import java.io.File;
import java.util.HashMap;

/**
 * Класс, содержащий генераторы для отчетов
 */
public class ReportGenerator {
    /**
     * Метод для генерации отчета на основе XML файла и сохранения в формате PDF.
     * @param reportPath путь к файлу отчета (.jrxml)
     * @param xmlFilePath путь к XML файлу с данными
     * @param outputFilePath путь для сохранения выходного PDF файла
     * @throws JRException при возникновении ошибок JasperReports
     */
    public void generatePdfReport(String reportPath, String xmlFilePath, String outputFilePath) throws JRException {
        generateReport(reportPath, xmlFilePath, outputFilePath, ReportType.PDF);
    }

    /**
     * Метод для генерации отчета на основе XML файла и сохранения в формате HTML.
     * @param reportPath путь к файлу отчета (.jrxml)
     * @param xmlFilePath путь к XML файлу с данными
     * @param outputFilePath путь для сохранения выходного HTML файла
     * @throws JRException при возникновении ошибок JasperReports
     */
    public void generateHtmlReport(String reportPath, String xmlFilePath, String outputFilePath) throws JRException {
        generateReport(reportPath, xmlFilePath, outputFilePath, ReportType.HTML);
    }

    /**
     * Общий метод для генерации отчетов.
     * @param reportPath путь к файлу отчета (.jrxml)
     * @param xmlFilePath путь к XML файлу с данными
     * @param outputFilePath путь для сохранения выходного файла
     * @param reportType тип отчета (PDF или HTML)
     * @throws JRException при возникновении ошибок JasperReports
     */
    private void generateReport(String reportPath, String xmlFilePath, String outputFilePath, ReportType reportType) throws JRException {
        // Проверяем наличие файла отчета
        File reportFile = new File(reportPath);
        if (!reportFile.exists()) {
            throw new RuntimeException("Файл отчета не найден: " + reportPath);
        }

        // Проверяем наличие XML файла с данными
        File xmlFile = new File(xmlFilePath);
        if (!xmlFile.exists()) {
            throw new RuntimeException("Файл XML данных не найден: " + xmlFilePath);
        }

        // Создаем источник данных из XML файла
        JRXmlDataSource xmlDataSource = new JRXmlDataSource(xmlFile, "/patients/patient");

        // Компилируем JRXML отчет
        JasperReport jasperReport = JasperCompileManager.compileReport(reportPath);

        // Параметры (если нужны, передаются в HashMap)
        HashMap<String, Object> parameters = new HashMap<>();

        // Заполняем отчет данными
        JasperPrint jasperPrint = JasperFillManager.fillReport(jasperReport, parameters, xmlDataSource);

        // Экспортируем отчет в соответствующий формат
        switch (reportType) {
            case PDF:
                JasperExportManager.exportReportToPdfFile(jasperPrint, outputFilePath);
                System.out.println("PDF отчет успешно создан: " + outputFilePath);
                break;

            case HTML:
                JasperExportManager.exportReportToHtmlFile(jasperPrint, outputFilePath);
                System.out.println("HTML отчет успешно создан: " + outputFilePath);
                break;
        }
    }

    // Перечисление для типов отчетов
    private enum ReportType {
        PDF, HTML
    }
}
