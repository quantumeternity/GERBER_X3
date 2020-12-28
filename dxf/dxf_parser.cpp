// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
/*******************************************************************************
*                                                                              *
* Author    :  Damir Bakiev                                                    *
* Version   :  na                                                              *
* Date      :  01 February 2020                                                *
* Website   :  na                                                              *
* Copyright :  Damir Bakiev 2016-2020                                          *
*                                                                              *
* License:                                                                     *
* Use, modification & distribution is subject to Boost Software License Ver 1. *
* http://www.boost.org/LICENSE_1_0.txt                                         *
*                                                                              *
*******************************************************************************/
#include "dxf_parser.h"
#include "dxf_file.h"

#include "section/dxf_blocks.h"
#include "section/dxf_entities.h"
#include "section/dxf_headerparser.h"
#include "section/dxf_tables.h"
//#include "section/dxf_classes.h"
//#include "section/dxf_objects.h"
//#include "section/dxf_thumbnailimage.h"

#include "tables/dxf_layer.h"

namespace Dxf {

Parser::Parser(QObject* parent)
    : FileParser(parent)
{
}

AbstractFile* Parser::parseFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return nullptr;

    m_file = new File;
    m_file->setFileName(fileName);

    int line = 1;

    Codes codes;
    codes.reserve(10000);

    QTextStream in(&file);

    auto getCode = [&in, &codes, &line, this] {
        // Code
        QString strCode(in.readLine());
        m_file->lines().append(strCode);
        bool ok;
        auto code(strCode.toInt(&ok));
        if (!ok)
            throw QString("Unknown code: raw str %1, line %2!").arg(strCode).arg(line);
        // Value
        QString strValue(in.readLine());
        m_file->lines().append(strValue);
        int multi = 0;
        while (strValue.endsWith("\\P")) {
            m_file->lines().append(in.readLine());
            strValue.append("\n" + m_file->lines().last());
            ++multi;
        }
        codes.emplace_back(code, strValue, line);
        line += 2 + multi;
        return *(codes.end() - 1);
    };

    try {
        do {
            getCode();
        } while (!in.atEnd() || *(codes.end() - 1) != "EOF");
        codes.shrink_to_fit();

        for (auto it = codes.begin(), from = codes.begin(), to = codes.begin(); it != codes.end(); ++it) {
            if (*it == "SECTION")
                from = it;
            if (auto it_ = it + 1; *it == "ENDSEC" && (*it_ == "SECTION" || *it_ == "EOF")) {
                to = it;
                const auto type = SectionParser::toType(*(from + 1));
                switch (type) {
                case SectionParser::HEADER:
                    dxfFile()->m_sections[type] = new SectionHEADER(dxfFile(), from, to);
                    break;
                case SectionParser::CLASSES:
                    //dxfFile()->m_sections[type] = new SectionCLASSES(dxfFile(), from, to);
                    break;
                case SectionParser::TABLES:
                    dxfFile()->m_sections[type] = new SectionTABLES(dxfFile(), from, to);
                    break;
                case SectionParser::BLOCKS:
                    dxfFile()->m_sections[type] = new SectionBLOCKS(dxfFile(), from, to);
                    break;
                case SectionParser::ENTITIES:
                    dxfFile()->m_sections[type] = new SectionENTITIES(dxfFile(), from, to);
                    break;
                case SectionParser::OBJECTS:
                    //dxfFile()->m_sections[type] = new SectionOBJECTS(dxfFile(), from, to);
                    break;
                case SectionParser::THUMBNAILIMAGE:
                    //dxfFile()->m_sections[type] = new SectionTHUMBNAILIMAGE(dxfFile(), from, to);
                    break;
                default:
                    throw QString("Unknowh Section!");
                    break;
                }
                if (dxfFile()->m_sections.contains(type))
                    dxfFile()->m_sections[type]->parse();
            }
        }
        file.close();
    } catch (const QString& wath) {
        qWarning() << "exeption QString:" << wath;
        emit fileError("", QFileInfo(fileName).fileName() + "\n" + wath);
        delete m_file;
        return nullptr;
    } catch (const std::exception& e) {
        qWarning() << "exeption:" << e.what();
        emit fileError("", QFileInfo(fileName).fileName() + "\n" + "Unknown Error! " + QString(e.what()));
        delete m_file;
        return nullptr;
    } catch (...) {
        qWarning() << "exeption:" << errno;
        emit fileError("", QFileInfo(fileName).fileName() + "\n" + "Unknown Error! " + QString::number(errno));
        delete m_file;
        return nullptr;
    }

    if (dxfFile()->m_sections.size() == 0) {
        delete m_file;
        m_file = nullptr;
    } else {
        emit fileReady(m_file);
    }
    return m_file;
}

bool Parser::isDxfFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
        return false;
    QTextStream in(&file);
    do {
        QString line(in.readLine());
        if (line.toInt() == 999) {
            line = in.readLine();
            line = in.readLine();
        }
        if (line.toInt() != 0)
            break;
        if (line = in.readLine(); line != "SECTION")
            break;
        if (line = in.readLine(); line.toInt() != 2)
            break;
        if (line = in.readLine(); line != "HEADER")
            break;
        return true;
    } while (false);
    return false;
}
}