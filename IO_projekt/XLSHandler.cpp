#include "XLSHandler.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <xmllite.h>
#include <atlbase.h>
#include <atlconv.h>

std::vector<std::vector<std::string>> XLSHandler::wczytaj_dane(const std::string& filePath) {
    std::vector<std::vector<std::string>> data;

    CComPtr<IXmlReader> pReader;
    CComPtr<IStream> pFileStream;
    HRESULT hr = SHCreateStreamOnFileA(filePath.c_str(), STGM_READ, &pFileStream);

    if (FAILED(hr)) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return data;
    }

    hr = CreateXmlReader(__uuidof(IXmlReader), (void**)&pReader, NULL);
    if (FAILED(hr)) {
        std::cerr << "Failed to create XML reader" << std::endl;
        return data;
    }

    hr = pReader->SetInput(pFileStream);
    if (FAILED(hr)) {
        std::cerr << "Failed to set input for XML reader" << std::endl;
        return data;
    }

    XmlNodeType nodeType;
    const wchar_t* pwszLocalName;
    while (S_OK == pReader->Read(&nodeType)) {
        if (nodeType == XmlNodeType_Element) {
            pReader->GetLocalName(&pwszLocalName, NULL);
            if (wcscmp(pwszLocalName, L"Patient") == 0) {
                std::vector<std::string> patientData;
                while (S_OK == pReader->Read(&nodeType)) {
                    if (nodeType == XmlNodeType_EndElement) break;
                    if (nodeType == XmlNodeType_Element) {
                        pReader->GetLocalName(&pwszLocalName, NULL);
                        std::wstring tagName(pwszLocalName);
                        pReader->Read(&nodeType);
                        if (nodeType == XmlNodeType_Text) {
                            const wchar_t* pwszValue;
                            pReader->GetValue(&pwszValue, NULL);
                            std::wstring value(pwszValue);
                            patientData.push_back(std::string(CW2A(value.c_str())));
                        }
                    }
                }
                data.push_back(patientData);
            }
        }
    }

    return data;
}